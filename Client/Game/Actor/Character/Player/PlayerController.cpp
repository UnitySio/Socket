#include "pch.h"
#include "PlayerController.h"

#include "DebugDrawHelper.h"
#include "Actor/Camera.h"
#include "Actor/Component/RigidBody2DComponent.h"
#include "Actor/Component/SpriteRendererComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Actor/Component/Animator/AnimationClip.h"
#include "Actor/Component/Animator/AnimatorComponent.h"
#include "Audio/AudioManager.h"
#include "Audio/Audio.h"
#include "Data/RegistryHelper.h"
#include "File/FileManager.h"
#include "Input/Keyboard.h"
#include "Resource/ResourceManager.h"
#include "Windows/DX/Sprite.h"

PlayerController::PlayerController(const std::wstring& kName) :
    CharacterBase(kName),
    last_pressed_jump_time_(0.f),
    jump_count_(0)
{
    capsule_collider_->SetSize({.5f, .5f});
    
    if (ResourceManager::Get()->Load<Sprite>(L"Soldier", L".\\Game_Data\\Soldier.png"))
    {
        sprite_ = ResourceManager::Get()->GetResource<Sprite>(L"Soldier");
    }
    
    sprite_->Split(9, 7, Sprite::kCenter);

    sprite_renderer_->SetSprite(sprite_);

    int temp[] = {0, 1, 2, 3, 4, 5};
    std::shared_ptr<AnimationClip> clip = animator_->AddClip(L"Idle", temp, 6);
    clip->SetRepeat(true);
    clip->SetFrameRate(6.f);

    int attack1_indices[] = { 18, 19, 20, 21, 22, 23 };
    clip = animator_->AddClip(L"Attack1", attack1_indices, 6);
    clip->SetRepeat(false);
    clip->SetFrameRate(15.f);

    int attack2_indices[] = { 27, 28, 29, 30, 31, 32 };
    clip = animator_->AddClip(L"Attack2", attack2_indices, 6);
    clip->SetRepeat(false);
    clip->SetFrameRate(15.f);

    int walk_indices[] = {9, 10, 11, 12, 13, 14, 15, 16};
    clip = animator_->AddClip(L"Walk", walk_indices, 8);
    clip->SetRepeat(true);
    clip->SetFrameRate(6.f);
    
    animator_->PlayClip(clip);

    GetTransform()->SetScale({2.f, 2.f});

    if (ResourceManager::Get()->Load<Audio>(L"BGM", FileManager::GetCurrentPath() + L"\\Game_Data\\BGM.mp3"))
    {
        Audio* audio = ResourceManager::Get()->GetResource<Audio>(L"BGM");
        audio->SetLoop(true);
        
        int id = AudioManager::Get()->PlaySound2D(audio);
    }
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

void PlayerController::Tick(float delta_time)
{
    CharacterBase::Tick(delta_time);

    last_pressed_jump_time_ -= delta_time;

    Keyboard* keyboard = Keyboard::Get();
    move_axis_.x = keyboard->GetKey(VK_RIGHT) - keyboard->GetKey(VK_LEFT);
    if (move_axis_.x != 0)
    {
        sprite_renderer_->SetFlipX(move_axis_.x < 0);
    }

    if (CanJump() && last_pressed_jump_time_ > 0.f)
    {
        last_grounded_time_ = 0.f;
        last_pressed_jump_time_ = 0.f;
        jump_count_++;

        Jump();
    }
    else if (is_jumping_ && last_pressed_jump_time_ > 0.f && jump_count_ < 2)
    {
        last_pressed_jump_time_ = 0.f;
        jump_count_++;
        
        Jump();
    }

    if (last_grounded_time_ > 0.f)
    {
        jump_count_ = 0;
    }
    
    if (keyboard->GetKeyDown('C'))
    {
        last_pressed_jump_time_ = .1f;
    }
    
}
