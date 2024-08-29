#include "pch.h"
#include "PlayerIdleState.h"
#include "PlayerAttackState.h"
#include "PlayerMoveState.h"

#include "Actor/Character/Player/PlayerController.h"
#include "Actor/Component/RigidBody2DComponent.h"
#include "Actor/Component/Animator/AnimatorComponent.h"
#include "Input/Keyboard.h"
#include "Math/Vector2.h"

PlayerIdleState::PlayerIdleState(StateMachine* owner) :
    State(owner)
{
}

void PlayerIdleState::OnTick(float delta_time)
{
    State::OnTick(delta_time);

    Keyboard* keyboard = Keyboard::Get();

    const float h = keyboard->IsKeyDown(VK_RIGHT) - keyboard->IsKeyDown(VK_LEFT);
    if (h != 0.f)
    {
        PlayerController* player = dynamic_cast<PlayerController*>(owner_);
        player->ChangeState(player->move_);
    }

    if (keyboard->IsKeyPressed('C'))
    {
        PlayerController* player = dynamic_cast<PlayerController*>(owner_);
        if (player)
        {
            RigidBody2DComponent* rigid_body = player->GetRigidBody();
            if (rigid_body)
            {
                rigid_body->AddForceY(5.f, ForceMode::kImpulse);
            }
        }
    }

    if (keyboard->IsKeyPressed('Z'))
    {
        PlayerController* player = dynamic_cast<PlayerController*>(owner_);
        if (player)
        {
            player->ChangeState(player->attack1_);
        }
    }
}

void PlayerIdleState::OnEnter()
{
    PlayerController* player = dynamic_cast<PlayerController*>(owner_);
    player->GetAnimator()->PlayClip(L"Idle");
}
