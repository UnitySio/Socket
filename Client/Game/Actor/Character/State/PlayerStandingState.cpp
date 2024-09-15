#include "pch.h"
#include "PlayerStandingState.h"

#include "Actor/Character/Player.h"
#include "Actor/Component/SpriteRendererComponent.h"
#include "Input/Keyboard.h"

PlayerStandingState::PlayerStandingState(Actor* owner, StateMachine* state_machine) :
    State(owner, state_machine)
{
}

void PlayerStandingState::Enter()
{
}

void PlayerStandingState::Exit()
{
}

void PlayerStandingState::Tick(float delta_time)
{
    Keyboard* keyboard = Keyboard::Get();
    float input_x = keyboard->GetKey(VK_RIGHT) - keyboard->GetKey(VK_LEFT);

    if (Player* player = static_cast<Player*>(owner_))
    {
        if (input_x != 0.f)
        {
            player->GetSpriteRenderer()->SetFlipX(input_x < 0.f);
        }
        
        Math::Vector2 velocity = player->GetVelocity();
        velocity.x = input_x * 5.f;
        player->SetVelocity(velocity);
    }
}
