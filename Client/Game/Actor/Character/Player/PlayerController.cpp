#include "pch.h"
#include "PlayerController.h"

#include "Actor/Box.h"
#include "Actor/Component/RigidBodyComponent.h"
#include "Actor/Component/SpriteRendererComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Actor/Component/Animator/AnimationClip.h"
#include "Actor/Component/Animator/AnimatorComponent.h"
#include "Audio/AudioManager.h"
#include "Data/DataManager.h"
#include "imgui/imgui.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include "Level/World.h"
#include "Windows/DX/Sprite.h"
#include "Logger/Logger.h"
#include "Resource/ResourceManager.h"
#include "States/PlayerIdleState.h"
#include "Windows/DX/UITexture.h"

PlayerController::PlayerController(const std::wstring& kName) :
    Super(kName)
{
    // ResourceManager::Get()->Load<Sprite>(L"Soldier", L".\\Game_Data\\Soldier.png");
    // Sprite* sprite = ResourceManager::Get()->GetResource<Sprite>(L"Soldier");
    
    sprite_ = std::make_shared<Sprite>();
    CHECK_IF(sprite_->Load(L".\\Game_Data\\Soldier.png"), L"Failed to load texture");
    
    sprite_->Split(9, 7, Sprite::kCenter);

    sprite_renderer_->SetSprite(sprite_);

    int temp[] = {0, 1, 2, 3, 4, 5};
    std::shared_ptr<AnimationClip> clip = animator_->AddClip(L"Idle", temp, 6);
    clip->SetRepeat(true);
    clip->SetFrameRate(6.f);

    int walk_indices[] = {9, 10, 11, 12, 13, 14, 15, 16};
    clip = animator_->AddClip(L"Walk", walk_indices, 8);
    clip->SetRepeat(true);
    clip->SetFrameRate(6.f);
    
    animator_->PlayClip(clip);

    GetTransform()->SetRelativeScale({2.f, 2.f});
    
    AudioManager::Get()->AddSound(L"BGM", L".\\Game_Data\\bgm.mp3");
    int id = AudioManager::Get()->PlaySound2D(L"BGM");

    // if (ResourceManager::Get()->Load<UITexture>(L"Soldier", L".\\Game_Data\\Soldier.png"))
    // {
    //     LOG(L"Success");
    // }

    ChangeState(std::make_shared<PlayerIdleState>(this));
}

void PlayerController::BeginPlay()
{
    Super::BeginPlay();

    float x = DataManager::GetFloat(L"PlayerX", 0.f);
    float y = DataManager::GetFloat(L"PlayerY", 0.f);
    GetTransform()->SetWorldPosition({x, y});
}

void PlayerController::EndPlay(EndPlayReason type)
{
    Super::EndPlay(type);
    
    Math::Vector2 position = GetTransform()->GetWorldPosition();
    DataManager::SetFloat(L"PlayerX", position.x);
    DataManager::SetFloat(L"PlayerY", position.y);
}

void PlayerController::PhysicsTick(float delta_time)
{
    Super::PhysicsTick(delta_time);

    Keyboard* keyboard = Keyboard::Get();

    const float h = keyboard->IsKeyDown(VK_RIGHT) - keyboard->IsKeyDown(VK_LEFT);
    if (h != 0.f)
    {
        sprite_renderer_->SetFlipX(h < 0.f);
        animator_->PlayClip(L"Walk");
    }
    else animator_->PlayClip(L"Idle");
    
    rigid_body_->SetVelocity({h * 2.f, rigid_body_->GetVelocity().y});
}

void PlayerController::Tick(float delta_time)
{
    Super::Tick(delta_time);
    
    Keyboard* keyboard = Keyboard::Get();
    
    if (keyboard->IsKeyPressed('Z'))
    {
        Box* box = SpawnActor<Box>(L"Box");
        box->GetTransform()->SetRelativePosition(GetTransform()->GetWorldPosition());
    }
}
