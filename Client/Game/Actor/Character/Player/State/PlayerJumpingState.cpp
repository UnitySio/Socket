#include "pch.h"
#include "PlayerJumpingState.h"

#include "Actor/Character/Player/Player.h"
#include "Actor/Component/Controller2DComponent.h"
#include "Actor/Component/SpriteRendererComponent.h"
#include "Input/Keyboard.h"
#include "Math/Math.h"

PlayerJumpingState::PlayerJumpingState(Actor* actor, StateMachine* state_machine) :
    State(actor, state_machine),
    player_(nullptr),
    controller_(nullptr),
    input_x_(0),
    jump_count_(0),
    velocity_(Math::Vector2::Zero())
{
}

void PlayerJumpingState::Enter()
{
    player_ = dynamic_cast<Player*>(owner_);
    if (player_)
    {
        sprite_renderer_ = player_->GetSpriteRenderer();
        controller_ = player_->GetController();

        const CollisionInfo& collisions = controller_->GetCollisions();
        if (collisions.sliding_down_max_slope)
        {
            // if (input_x_ != -Math::Sign(collisions.slope_normal.x))
            // {
            //     velocity_.y = player_->GetJumpVelocity() * collisions.slope_normal.y;
            //     velocity_.x = player_->GetJumpVelocity() * collisions.slope_normal.x;
            // }
            
            velocity_.y = player_->GetJumpVelocity() * collisions.slope_normal.y;
            velocity_.x = player_->GetJumpVelocity() * collisions.slope_normal.x;
        }
        else
        {
            velocity_.y = player_->GetJumpVelocity();
        }

        player_->SetLastPressedJumpTime(0.f);
        jump_count_++;
    }
}

void PlayerJumpingState::Exit()
{
    velocity_ = Math::Vector2::Zero();
    input_x_ = 0;
    jump_count_ = 0;
}

void PlayerJumpingState::PhysicsTick(float delta_time)
{
    velocity_.x = player_->GetMoveSpeed() * input_x_;
    velocity_.y += player_->GetGravity() * delta_time;

    if (controller_)
    {
        controller_->Move(velocity_ * delta_time);

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
    Keyboard* keyboard = Keyboard::Get();
    input_x_ = keyboard->GetKey(VK_RIGHT) - keyboard->GetKey(VK_LEFT);
    if (sprite_renderer_ && input_x_ != 0)
    {
        sprite_renderer_->SetFlipX(input_x_ < 0);
    }
}

void PlayerJumpingState::PostTick(float delta_time)
{
}
