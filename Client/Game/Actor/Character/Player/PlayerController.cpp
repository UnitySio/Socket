#include "pch.h"
#include "PlayerController.h"

#include "DebugDrawHelper.h"
#include "Actor/Camera.h"
#include "Actor/Component/CapsuleColliderComponent.h"
#include "Actor/Component/RigidBody2DComponent.h"
#include "Actor/Component/SpriteRendererComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Actor/Component/Animator/AnimationClip.h"
#include "Actor/Component/Animator/AnimatorComponent.h"
#include "Audio/AudioManager.h"
#include "Data/RegistryHelper.h"
#include "Input/Keyboard.h"
#include "Level/World.h"
#include "Windows/DX/Sprite.h"
#include "States/PlayerIdleState.h"
#include "States/PlayerAttackState.h"
#include "Windows/DX/UITexture.h"

PlayerController::PlayerController(const std::wstring& kName) :
    CharacterBase(kName),
    is_hit_(false)
{
    // ResourceManager::Get()->Load<Sprite>(L"Soldier", L".\\Game_Data\\Soldier.png");
    // Sprite* sprite = ResourceManager::Get()->GetResource<Sprite>(L"Soldier");

    capsule_collider_->SetSize({.5f, .5f});
    
    sprite_ = std::make_shared<Sprite>();
    CHECK_IF(sprite_->Load(L".\\Game_Data\\Soldier.png"), L"Failed to load texture");
    
    sprite_->Split(9, 7, Sprite::kCenter);

    sprite_renderer_->SetSprite(sprite_);

    int temp[] = {0, 1, 2, 3, 4, 5};
    std::shared_ptr<AnimationClip> clip = animator_->AddClip(L"Idle", temp, 6);
    clip->SetRepeat(true);
    clip->SetFrameRate(6.f);
    idle_ = std::make_shared<PlayerIdleState>(this);

    int attack1_indices[] = { 18, 19, 20, 21, 22, 23 };
    clip = animator_->AddClip(L"Attack1", attack1_indices, 6);
    clip->AddEvent([this]()-> void { ChangeState(idle_); }, 5);
    clip->SetRepeat(false);
    clip->SetFrameRate(15.f);
    attack1_ = std::make_shared<PlayerAttackState>(this);

    int attack2_indices[] = { 27, 28, 29, 30, 31, 32 };
    clip = animator_->AddClip(L"Attack2", attack2_indices, 6);
    clip->AddEvent([this]()-> void { ChangeState(idle_); }, 5);
    clip->SetRepeat(false);
    clip->SetFrameRate(15.f);
    attack2_ = std::make_shared<PlayerAttack2State>(this);

    int walk_indices[] = {9, 10, 11, 12, 13, 14, 15, 16};
    clip = animator_->AddClip(L"Walk", walk_indices, 8);
    clip->SetRepeat(true);
    clip->SetFrameRate(6.f);
    move_ = std::make_shared<PlayerMoveState>(this);
    
    animator_->PlayClip(clip);

    GetTransform()->SetScale({2.f, 2.f});
    
    AudioManager::Get()->LoadSound(L"BGM", L".\\Game_Data\\bgm.mp3");
    int id = AudioManager::Get()->PlaySound2D(L"BGM");

    // if (ResourceManager::Get()->Load<UITexture>(L"Soldier", L".\\Game_Data\\Soldier.png"))
    // {
    //     LOG(L"Success");
    // }

    ChangeState(idle_);
}

void PlayerController::Tick(float delta_time)
{
    CharacterBase::Tick(delta_time);

    Math::Vector2 position = GetTransform()->GetPosition();
    DebugDrawHelper::Get()->DrawCircle(position, .5f, Math::Color::Red);
}

void PlayerController::BeginPlay()
{
    CharacterBase::BeginPlay();

    Camera::Get()->SetTarget(this);

    float x = RegistryHelper::GetFloat(L"PlayerX", 0.f);
    float y = RegistryHelper::GetFloat(L"PlayerY", 0.f);
    GetTransform()->SetPosition({x, y});
}

void PlayerController::EndPlay(EndPlayReason type)
{
    CharacterBase::EndPlay(type);
    
    Math::Vector2 position = GetTransform()->GetPosition();
    RegistryHelper::SetFloat(L"PlayerX", position.x);
    RegistryHelper::SetFloat(L"PlayerY", position.y);
}
