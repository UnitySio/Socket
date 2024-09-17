#include "pch.h"
#include "PlayerStandingState.h"

#include "Actor/Character/Player/Player.h"
#include "Actor/Component/Controller2DComponent.h"
#include "Actor/Component/SpriteRendererComponent.h"
#include "Input/Keyboard.h"

PlayerStandingState::PlayerStandingState(Actor* actor, StateMachine* state_machine) :
    State(actor, state_machine),
    player_(nullptr),
    sprite_renderer_(nullptr),
    controller_(nullptr),
    input_x_(0),
    velocity_(Math::Vector2::Zero()),
    last_grounded_time_(0.f),
    coyote_time_(.15f)
{
}

void PlayerStandingState::Enter()
{
    player_ = dynamic_cast<Player*>(owner_);
    if (player_)
    {
        sprite_renderer_ = player_->GetSpriteRenderer();
        controller_ = player_->GetController();
    }
}

void PlayerStandingState::Exit()
{
    velocity_ = Math::Vector2::Zero();
    input_x_ = 0;
    last_grounded_time_ = 0.f;
}

void PlayerStandingState::PhysicsTick(float delta_time)
{
    velocity_.x = player_->GetMoveSpeed() * input_x_;
    velocity_.y += player_->GetGravity() * delta_time;
    
    if (controller_)
    {
        controller_->Move(velocity_ * delta_time);

        const CollisionInfo& collisions = controller_->GetCollisions();

        if (controller_->IsGrounded())
        {
            last_grounded_time_ = coyote_time_;

            if (collisions.sliding_down_max_slope)
                velocity_.y += collisions.slope_normal.y * -player_->GetGravity() * delta_time;
            else velocity_.y = 0.f;
        }
    }
}

void PlayerStandingState::Tick(float delta_time)
{
    last_grounded_time_ -= delta_time;
    
    if (last_grounded_time_ > 0.f && player_->GetLastPressedJumpTime() > 0.f)
    {
        state_machine_->ChangeState(player_->GetState(1));
        return;
    }
    
    Keyboard* keyboard = Keyboard::Get();
    input_x_ = keyboard->GetKey(VK_RIGHT) - keyboard->GetKey(VK_LEFT);
    if (sprite_renderer_ && input_x_ != 0)
    {
        sprite_renderer_->SetFlipX(input_x_ < 0);
    }
}

void PlayerStandingState::PostTick(float delta_time)
{
}
