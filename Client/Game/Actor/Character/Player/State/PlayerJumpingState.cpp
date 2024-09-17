#include "pch.h"
#include "PlayerJumpingState.h"

#include "Actor/Character/Player/Player.h"
#include "Actor/Component/Controller2DComponent.h"
#include "Input/Keyboard.h"

PlayerJumpingState::PlayerJumpingState(Actor* actor, StateMachine* state_machine) :
    State(actor, state_machine),
    player_(nullptr),
    controller_(nullptr),
    input_x_(0),
    velocity_(Math::Vector2::Zero())
{
}

void PlayerJumpingState::Enter()
{
    player_ = dynamic_cast<Player*>(owner_);
    if (player_)
    {
        controller_ = player_->GetController();
        
        velocity_.y = player_->GetJumpVelocity();
    }
}

void PlayerJumpingState::Exit()
{
    velocity_ = Math::Vector2::Zero();
}

void PlayerJumpingState::PhysicsTick(float delta_time)
{
    velocity_.x = player_->GetMoveSpeed() * input_x_;
    velocity_.y += player_->GetGravity() * delta_time;

    if (controller_)
    {
        controller_->Move(velocity_ * delta_time);

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
}

void PlayerJumpingState::PostTick(float delta_time)
{
}
