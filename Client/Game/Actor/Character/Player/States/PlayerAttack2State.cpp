#include "pch.h"
#include "PlayerAttack2State.h"

#include "Actor/Character/Player/PlayerController.h"
#include "Input/Keyboard.h"
#include "Math/Vector2.h"
#include "Actor/Component/Animator/AnimatorComponent.h"

PlayerAttack2State::PlayerAttack2State(StateMachine* owner) :
    State(owner)
{
}

void PlayerAttack2State::OnTick(float delta_time)
{
    State::OnTick(delta_time);

    Keyboard* keyboard = Keyboard::Get();
}

void PlayerAttack2State::OnEnter()
{
    State::OnEnter();

    PlayerController* player = dynamic_cast<PlayerController*>(owner_);
    if (IsValid(player)) player->GetAnimator()->PlayClip(L"Attack2");
}