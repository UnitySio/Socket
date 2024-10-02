#include "pch.h"
#include "PlayerStandingState.h"

#include "Actor/Character/Player/Player.h"
#include "Actor/Component/Controller2DComponent.h"
#include "Actor/Component/SpriteRendererComponent.h"
#include "Actor/Component/Animator/AnimatorComponent.h"
#include "Input/Keyboard.h"
#include "Math/Math.h"

PlayerStandingState::PlayerStandingState(Actor* actor, StateMachine* state_machine) :
    State(actor, state_machine),
    player_(nullptr),
    sprite_renderer_(nullptr),
    controller_(nullptr),
    input_x_(0),
    last_grounded_time_(0.f),
    coyote_time_(.15f),
    last_double_tap_time_(0.f),
    is_running_(false),
    velocity_(Math::Vector2::Zero())
{
}

void PlayerStandingState::Enter()
{
    player_ = dynamic_cast<Player*>(owner_);
    if (player_)
    {
        sprite_renderer_ = player_->GetSpriteRenderer();
        animator_ = player_->GetAnimator();
        controller_ = player_->GetController();

        animator_->PlayClip(L"Idle");
    }
}

void PlayerStandingState::Exit()
{
    input_x_ = 0;
    
    last_grounded_time_ = 0.f;
    last_double_tap_time_ = 0.f;

    velocity_ = Math::Vector2::Zero();
}

void PlayerStandingState::PhysicsTick(float delta_time)
{
}

void PlayerStandingState::Tick(float delta_time)
{
    HandleTime(delta_time);
    
    velocity_.x = input_x_ * player_->GetMoveSpeed();
    velocity_.y += player_->GetGravity() * delta_time;

    controller_->Move(velocity_ * delta_time);
    
    const CollisionInfo& collisions = controller_->GetCollisions();
    if (collisions.above || collisions.below)
    {
        if (collisions.sliding_down_max_slope)
            velocity_.y += collisions.slope_normal.y * -player_->GetGravity() * delta_time;
        else velocity_.y = 0.f;
    }

    if (collisions.below)
    {
        last_grounded_time_ = coyote_time_;
    }
    
    Keyboard* keyboard = Keyboard::Get();
    input_x_ = keyboard->GetKey(VK_RIGHT) - keyboard->GetKey(VK_LEFT);
    if (Math::Abs(input_x_) > 0)
    {
        if (sprite_renderer_) sprite_renderer_->SetFlipX(input_x_ < 0);
        if (animator_)
        {
            if (is_running_)
            {
                player_->SetMoveSpeed(6.f);
                animator_->PlayClip(L"Run");
            }
            else
            {
                player_->SetMoveSpeed(3.f);
                animator_->PlayClip(L"Walk");
            }
        }
    }
    else
    {
        if (animator_) animator_->PlayClip(L"Idle");
    }

    if (keyboard->GetKeyDown(VK_LEFT) || keyboard->GetKeyDown(VK_RIGHT))
    {
        if (last_double_tap_time_ > 0.f)
        {
            is_running_ = true;
            last_double_tap_time_ = 0.f;
        }
        else
        {
            last_double_tap_time_ = .2f;
        }
    }

    if (is_running_ && !keyboard->GetKey(VK_LEFT) && !keyboard->GetKey(VK_RIGHT))
    {
        is_running_ = false;
    }

    if (last_grounded_time_ > 0.f && player_->GetLastPressedJumpTime() > 0.f)
    {
        player_->ResetLastPressedJumpTime();
        state_machine_->ChangeState(player_->GetState(1));
        return;
    }
}

void PlayerStandingState::PostTick(float delta_time)
{
}

void PlayerStandingState::HandleTime(float delta_time)
{
    const CollisionInfo& collisions = controller_->GetCollisions();
    if (collisions.below && last_grounded_time_ > 0.f)
    {
        last_grounded_time_ = Math::Max(last_grounded_time_ - delta_time, 0.f);
    }
    
    if (last_double_tap_time_ > 0.f)
    {
        last_double_tap_time_ = Math::Max(last_double_tap_time_ - delta_time, 0.f);
    }
}
