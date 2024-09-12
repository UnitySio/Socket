#include "pch.h"
#include "LocomotionState.h"

#include "Actor/Component/RigidBody2DComponent.h"
#include "Actor/Component/SpriteRendererComponent.h"
#include "Actor/Component/Animator/AnimatorComponent.h"

Player::LocomotionState::LocomotionState(StateMachine* owner) :
    State(owner),
    player_(nullptr)
{
}

void Player::LocomotionState::OnEnter()
{
    State::OnEnter();

    PlayerController* player = dynamic_cast<PlayerController*>(owner_);
    CHECK(IsValid(player));

    player_ = player;
    
    AnimatorComponent* animator = player_->GetAnimator();
    CHECK(animator);

    animator_ = animator;
    animator_->PlayClip(L"Idle");
}

void Player::LocomotionState::OnPhysicsTick(float delta_time)
{
    State::OnPhysicsTick(delta_time);

    RigidBody2DComponent* rigid_body = player_->GetRigidBody();
    if (!rigid_body) return;

    Math::Vector2 input_axis = player_->GetInputAxis();
    if (input_axis.x != 0.f)
    {
        rigid_body->SetLinearVelocityX(input_axis.x * 3.f);
    }
}

void Player::LocomotionState::OnTick(float delta_time)
{
    State::OnTick(delta_time);

    Math::Vector2 input_axis = player_->GetInputAxis();

    if (input_axis.x != 0.f)
    {
        animator_->PlayClip(L"Walk");
        player_->GetSpriteRenderer()->SetFlipX(input_axis.x < 0.f);
    }
    else
    {
        animator_->PlayClip(L"Idle");
    }
}
