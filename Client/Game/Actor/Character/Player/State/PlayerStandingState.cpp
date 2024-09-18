#include "pch.h"
#include "PlayerStandingState.h"

#include "Actor/Character/Player/Player.h"
#include "Actor/Component/Controller2DComponent.h"
#include "Actor/Component/SpriteRendererComponent.h"
#include "Actor/Component/Animator/AnimatorComponent.h"

PlayerStandingState::PlayerStandingState(Actor* actor, StateMachine* state_machine) :
    State(actor, state_machine),
    player_(nullptr),
    sprite_renderer_(nullptr),
    controller_(nullptr),
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
        animator_ = player_->GetAnimator();
        controller_ = player_->GetController();

        animator_->PlayClip(L"Idle");
    }
}

void PlayerStandingState::Exit()
{
    velocity_ = Math::Vector2::Zero();
    last_grounded_time_ = 0.f;
}

void PlayerStandingState::PhysicsTick(float delta_time)
{
    velocity_.x = player_->GetMoveSpeed() * player_->GetInputX();
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
    
    if (sprite_renderer_ && player_->GetInputX() != 0)
    {
        sprite_renderer_->SetFlipX(player_->GetInputX() < 0);
    }

    if (player_->GetInputX() != 0) animator_->PlayClip(L"Walk");
    else animator_->PlayClip(L"Idle");
}

void PlayerStandingState::PostTick(float delta_time)
{
}
