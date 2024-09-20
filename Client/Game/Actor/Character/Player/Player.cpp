#include "pch.h"
#include "Player.h"

#include "Actor/Camera.h"
#include "Actor/Component/Controller2DComponent.h"
#include "Actor/Component/SpriteRendererComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Actor/Component/Animator/AnimationClip.h"
#include "Actor/Component/Animator/AnimatorComponent.h"
#include "Input/Keyboard.h"
#include "Math/Math.h"
#include "Resource/ResourceManager.h"
#include "State/PlayerJumpingState.h"
#include "State/PlayerStandingState.h"
#include "Windows/DX/Sprite.h"

Player::Player(const std::wstring& kName) :
    CharacterBase(kName),
    gravity_(0.f),
    jump_height_(2.f),
    time_to_jump_apex_(.4f),
    jump_velocity_(0.f),
    last_grounded_time_(0.f),
    coyote_time_(.15f),
    last_pressed_jump_time_(0.f),
    velocity_(Math::Vector2::Zero())
{
    GetTransform()->SetPosition({5.f, 5.f});
    
    if (ResourceManager::Get()->Load<Sprite>(L"PlayerSheet", L".\\Game_Data\\PlayerSheet.png"))
    {
        sprite_ = ResourceManager::Get()->GetResource<Sprite>(L"PlayerSheet");
        sprite_->Split(9, 7, Sprite::kCenter);
        
        sprite_renderer_->SetSprite(sprite_);
    }
    
    {
        int idle_indices[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        std::shared_ptr<AnimationClip> idle_clip = animator_->AddClip(L"Idle", idle_indices, 9);
        idle_clip->SetRepeat(true);
        idle_clip->SetFrameRate(6.f);

        int walk_indices[] = {9, 10, 11, 12, 13, 14, 15, 16};
        std::shared_ptr<AnimationClip> walk_clip = animator_->AddClip(L"Walk", walk_indices, 8);
        walk_clip->SetRepeat(true);
        walk_clip->SetFrameRate(10.f);

        int run_indices[] = {27, 28, 29, 30, 31, 32};
        std::shared_ptr<AnimationClip> run_clip = animator_->AddClip(L"Run", run_indices, 6);
        run_clip->SetRepeat(true);
        run_clip->SetFrameRate(10.f);

        int jump_indices[] = {36, 37, 38};
        std::shared_ptr<AnimationClip> jump_clip = animator_->AddClip(L"Jump", jump_indices, 3);
        jump_clip->SetRepeat(false);
        jump_clip->SetFrameRate(10.f);
    }

    states_[0] = std::make_unique<PlayerStandingState>(this, state_machine_.get());
    states_[1] = std::make_unique<PlayerJumpingState>(this, state_machine_.get());
}

void Player::BeginPlay()
{
    CharacterBase::BeginPlay();

    Camera::Get()->SetTarget(this);

    state_machine_->ChangeState(states_[0].get());

    gravity_ = -(2 * jump_height_) / std::pow(time_to_jump_apex_, 2);
    jump_velocity_ = Math::Abs(gravity_) * time_to_jump_apex_;
}

void Player::PhysicsTick(float delta_time)
{
    CharacterBase::PhysicsTick(delta_time);

    const CollisionInfo& collisions = controller_->GetCollisions();
    if (collisions.above || collisions.below)
    {
        if (collisions.sliding_down_max_slope)
            velocity_.y += collisions.slope_normal.y * -gravity_ * delta_time;
        else velocity_.y = 0.f;
    }

    if (collisions.below)
    {
        last_grounded_time_ = coyote_time_;
    }
}

void Player::Tick(float delta_time)
{
    CharacterBase::Tick(delta_time);

    HandleTime(delta_time);

    Keyboard* keyboard = Keyboard::Get();
    if (keyboard->GetKeyDown('C'))
    {
        last_pressed_jump_time_ = .1f;
    }
}

void Player::HandleTime(float delta_time)
{
    const CollisionInfo& collisions = controller_->GetCollisions();
    if (!collisions.below && last_grounded_time_ > 0.f)
    {
        last_grounded_time_ = Math::Max(last_grounded_time_ - delta_time, 0.f);
    }

    if (last_pressed_jump_time_ > 0.f)
    {
        last_pressed_jump_time_ = Math::Max(last_pressed_jump_time_ - delta_time, 0.f);
    }
}
