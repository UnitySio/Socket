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
#include "States/PlayerAttackState.h"
#include "Windows/DX/UITexture.h"

PlayerController::PlayerController(const std::wstring& kName) :
    CharacterBase(kName)
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

    int attack1_indices[] = { 18, 19, 20, 21, 22, 23 };
    clip = animator_->AddClip(L"Attack1", attack1_indices, 6);
    clip->AddEvent([this]()-> void {ChangeState(std::make_shared<PlayerIdleState>(this)); }, 5);
    clip->SetRepeat(false);
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
    CharacterBase::BeginPlay();

    float x = DataManager::GetFloat(L"PlayerX", 0.f);
    float y = DataManager::GetFloat(L"PlayerY", 0.f);
    GetTransform()->SetWorldPosition({x, y});
}

void PlayerController::EndPlay(EndPlayReason type)
{
    CharacterBase::EndPlay(type);
    
    Math::Vector2 position = GetTransform()->GetWorldPosition();
    DataManager::SetFloat(L"PlayerX", position.x);
    DataManager::SetFloat(L"PlayerY", position.y);
}

void PlayerController::PhysicsTick(float delta_time)
{
    CharacterBase::PhysicsTick(delta_time);

    Keyboard* keyboard = Keyboard::Get();
}

void PlayerController::Tick(float delta_time)
{
    CharacterBase::Tick(delta_time);
    
    Keyboard* keyboard = Keyboard::Get();
    
    /*if (keyboard->IsKeyPressed('Z'))
    {
        Box* box = SpawnActor<Box>(L"Box");
        box->GetTransform()->SetRelativePosition(GetTransform()->GetWorldPosition());
    }*/
}
