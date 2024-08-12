#include "pch.h"
#include "PlayerIdleState.h"

#include "Actor/Character/Player/PlayerController.h"
#include "Actor/Component/RigidBodyComponent.h"
#include "Input/Keyboard.h"
#include "Math/Vector2.h"

PlayerIdleState::PlayerIdleState(StateMachine* owner) :
    State(owner)
{
}

void PlayerIdleState::OnUpdate(float delta_time)
{
    State::OnUpdate(delta_time);

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
}
