#include "pch.h"
#include "PlayerAttackState.h"

#include "Actor/Character/Player/PlayerController.h"
#include "Input/Keyboard.h"
#include "Math/Vector2.h"
#include "Actor/Component/Animator/AnimatorComponent.h"

PlayerAttackState::PlayerAttackState(StateMachine* owner) :
    State(owner)
{
}

void PlayerAttackState::OnTick(float delta_time)
{
    State::OnTick(delta_time);

    Keyboard* keyboard = Keyboard::Get();
}

void PlayerAttackState::OnEnter()
{
    State::OnEnter();

    PlayerController* player = dynamic_cast<PlayerController*>(owner_);
    if(IsValid(player)) player->GetAnimator()->PlayClip(L"Attack1");
}