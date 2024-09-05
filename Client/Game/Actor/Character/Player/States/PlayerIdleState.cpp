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

    const float h = keyboard->GetKey(VK_RIGHT) - keyboard->GetKey(VK_LEFT);
    if (h != 0.f)
    {
        PlayerController* player = dynamic_cast<PlayerController*>(owner_);
        
        if(IsValid(player)) player->ChangeState(player->move_);
    }

    if (keyboard->GetKeyDown('C'))
    {
        PlayerController* player = dynamic_cast<PlayerController*>(owner_);
        if(IsValid(player))
        {
            RigidBody2DComponent* rigid_body = player->GetRigidBody();
            if (rigid_body)
            {
                rigid_body->AddForceY(5.f, ForceMode::kImpulse);
            }
        }
    }

    if (keyboard->GetKeyDown('Z'))
    {
        keyboard->command_buffer_.pop();

        PlayerController* player = dynamic_cast<PlayerController*>(owner_);
        if (!IsValid(player)) return;

        if (keyboard->command_buffer_.empty())
        {
            player->ChangeState(player->attack1_);
        }
        else
        {
            KeyEvent event = keyboard->command_buffer_.top();
            if (event.key_code == VK_DOWN) player->ChangeState(player->attack2_);
        }

        while (!keyboard->command_buffer_.empty()) keyboard->command_buffer_.pop();
    }
}

void PlayerIdleState::OnEnter()
{
    PlayerController* player = dynamic_cast<PlayerController*>(owner_);
    if(IsValid(player)) player->GetAnimator()->PlayClip(L"Idle");
}
