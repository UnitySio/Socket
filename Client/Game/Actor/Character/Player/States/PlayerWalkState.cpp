#include "pch.h"
#include "PlayerWalkState.h"

#include "Actor/Character/Player/PlayerController.h"
#include "Actor/Component/RigidBody2DComponent.h"
#include "Actor/Component/SpriteRendererComponent.h"
#include "Actor/Component/Animator/AnimatorComponent.h"
#include "Misc/EngineMacros.h"

PlayerWalkState::PlayerWalkState(StateMachine* owner) :
    State(owner),
    player_(nullptr)
{
}

void PlayerWalkState::OnEnter()
{
    State::OnEnter();
    
    PlayerController* player = dynamic_cast<PlayerController*>(owner_);
    CHECK(player);

    player_ = player;
    player_->GetAnimator()->PlayClip(L"Walk");
}

void PlayerWalkState::OnPhysicsTick(float delta_time)
{
    State::OnPhysicsTick(delta_time);

    RigidBody2DComponent* rigid_body = player_->GetRigidBody();
    rigid_body->SetLinearVelocityX(player_->GetInputAxis().x * 3.f);
}

void PlayerWalkState::OnTick(float delta_time)
{
    State::OnTick(delta_time);
    
    if (player_->GetInputAxis().x == 0.f)
    {
        player_->ChangeState(player_->GetState(PlayerStates::kIdle));
        return;
    }

    player_->GetSpriteRenderer()->SetFlipX(player_->GetInputAxis().x < 0.f);
}
