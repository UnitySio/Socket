#include "pch.h"
#include "PlayerIdleState.h"
#include "PlayerAttackState.h"

#include "Actor/Character/Player/PlayerController.h"
#include "Actor/Component/RigidBodyComponent.h"
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

    if (keyboard->IsKeyPressed('C'))
    {
        PlayerController* player = dynamic_cast<PlayerController*>(owner_);
        if (player)
        {
            RigidBodyComponent* rigid_body = player->GetRigidBody();
            if (rigid_body)
            {
                rigid_body->SetVelocity(Math::Vector2::Zero());
                rigid_body->AddForce(Math::Vector2::Up() * 5.f, ForceMode::kImpulse);
            }
        }
    }

    if (keyboard->IsKeyPressed('Z'))
    {
        PlayerController* player = dynamic_cast<PlayerController*>(owner_);
        if (player)
        {
            //owner_->ChangeState(std::make_shared<PlayerAttackState>(this));
        }

    }
}
