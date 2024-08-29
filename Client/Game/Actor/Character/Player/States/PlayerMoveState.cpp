#include "pch.h"
#include "PlayerMoveState.h"
#include "PlayerIdleState.h"

#include "Actor/Character/Player/PlayerController.h"
#include "Input/Keyboard.h"
#include "Math/Vector2.h"
#include "Actor/Component/SpriteRendererComponent.h"
#include "Actor/Component/Animator/AnimatorComponent.h"
#include "Actor/Component/RigidBody2DComponent.h"

PlayerMoveState::PlayerMoveState(StateMachine* owner) :
    State(owner)
{
}

void PlayerMoveState::OnPhysicsTick(float delta_time)
{
    State::OnPhysicsTick(delta_time);

    PlayerController* player = dynamic_cast<PlayerController*>(owner_);

    Keyboard* keyboard = Keyboard::Get();
    const float h = keyboard->IsKeyDown(VK_RIGHT) - keyboard->IsKeyDown(VK_LEFT);
    if (h == 0.f)
    {
        player->ChangeState(std::make_shared<PlayerIdleState>(player));
        return;
    }

    SpriteRendererComponent* sprite = player->GetSpriteRenderer();
    sprite->SetFlipX(h < 0.f);

    RigidBody2DComponent* rigidbody = player->GetRigidBody();
    rigidbody->SetLinearVelocityX(h * 2.f);
}

void PlayerMoveState::OnTick(float delta_time)
{
    State::OnTick(delta_time);

    Keyboard* keyboard = Keyboard::Get();
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
}

void PlayerMoveState::OnEnter()
{
    State::OnEnter();

    PlayerController* player = dynamic_cast<PlayerController*>(owner_);
    player->GetAnimator()->PlayClip(L"Walk");
}