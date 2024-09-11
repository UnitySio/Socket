#include "pch.h"
#include "PlayerIdleState.h"
#include "Actor/Character/Player/PlayerController.h"
#include "Actor/Component/Animator/AnimatorComponent.h"

PlayerIdleState::PlayerIdleState(StateMachine* owner) :
    State(owner),
    player_(nullptr)
{
}

void PlayerIdleState::OnEnter()
{
    State::OnEnter();

    PlayerController* player = dynamic_cast<PlayerController*>(owner_);
    CHECK(player);

    player_ = player;
    player_->GetAnimator()->PlayClip(L"Idle");
}

void PlayerIdleState::OnTick(float delta_time)
{
    State::OnTick(delta_time);

    if (player_->GetInputAxis().x != 0.f)
    {
        player_->ChangeState(player_->GetState(PlayerStates::kWalk));
    }
}
