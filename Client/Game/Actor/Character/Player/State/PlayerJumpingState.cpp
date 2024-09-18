#include "pch.h"
#include "PlayerJumpingState.h"

#include "Actor/Character/Player/Player.h"
#include "Actor/Component/Controller2DComponent.h"
#include "Actor/Component/SpriteRendererComponent.h"
#include "Actor/Component/Animator/AnimatorComponent.h"
#include "Math/Math.h"

PlayerJumpingState::PlayerJumpingState(Actor* actor, StateMachine* state_machine) :
    State(actor, state_machine),
    player_(nullptr),
    sprite_renderer_(nullptr),
    controller_(nullptr),
    jump_count_(0),
    is_sliding_(false),
    velocity_(Math::Vector2::Zero()),
    input_velocity_(Math::Vector2::Zero())
{
}

void PlayerJumpingState::Enter()
{
    player_ = dynamic_cast<Player*>(owner_);
    if (player_)
    {
        sprite_renderer_ = player_->GetSpriteRenderer();
        animator_ = player_->GetAnimator();
        controller_ = player_->GetController();

        const CollisionInfo& collisions = controller_->GetCollisions();
        if (collisions.sliding_down_max_slope)
        {
            if (player_->GetInputX() != -Math::Sign(collisions.slope_normal.x))
            {
                velocity_.y = player_->GetJumpVelocity() * collisions.slope_normal.y;
                velocity_.x = player_->GetJumpVelocity() * collisions.slope_normal.x;
                is_sliding_ = true;
            }
        }
        else
        {
            velocity_.y = player_->GetJumpVelocity();
        }

        player_->SetLastPressedJumpTime(0.f);
        jump_count_++;

        animator_->PlayClip(L"Jump");
    }
}

void PlayerJumpingState::Exit()
{
    input_velocity_ = Math::Vector2::Zero();
    velocity_ = Math::Vector2::Zero();
    jump_count_ = 0;
    is_sliding_ = false;
}

void PlayerJumpingState::PhysicsTick(float delta_time)
{
    if (!is_sliding_) input_velocity_.x = player_->GetMoveSpeed() * player_->GetInputX();
    velocity_.y += player_->GetGravity() * delta_time;

    if (controller_)
    {
        controller_->Move(input_velocity_ * delta_time + velocity_ * delta_time);

        if (player_->GetLastPressedJumpTime() > 0.f && jump_count_ < 2)
        {
            player_->SetLastPressedJumpTime(0.f);
            velocity_.y = player_->GetJumpVelocity();
            jump_count_++;
        }

        if (controller_->IsCeiling())
        {
            velocity_.y = 0.f;
        }

        if (controller_->IsGrounded())
        {
            state_machine_->ChangeState(player_->GetState(0));
            return;
        }
    }
}

void PlayerJumpingState::Tick(float delta_time)
{
    if (sprite_renderer_ && player_->GetInputX() != 0)
    {
        sprite_renderer_->SetFlipX(player_->GetInputX() < 0);
    }
}

void PlayerJumpingState::PostTick(float delta_time)
{
}
