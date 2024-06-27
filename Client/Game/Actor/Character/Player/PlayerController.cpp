#include "PlayerController.h"
#include "Windows.h"

#include "Actor/Component/BoxColliderComponent.h"
#include "Actor/Component/RigidBodyComponent.h"
#include "Actor/Component/InputComponent.h"

PlayerController::PlayerController(const std::wstring& kName) : CharacterBase(kName)
{
    input_ = CreateComponent<InputComponent>(L"Input");
    input_->RegisterKey(VK_RIGHT);
    input_->RegisterKey(VK_LEFT);
    input_->RegisterKey(VK_SPACE);
    
}

void PlayerController::PhysicsTick(float delta_time)
{
    CharacterBase::PhysicsTick(delta_time);
    
    float h = input_->IsKeyPressed(VK_RIGHT) - input_->IsKeyPressed(VK_LEFT);
    
    rigid_body_->SetVelocity({h * 6.f, rigid_body_->GetVelocity().y});
}

void PlayerController::Tick(float delta_time)
{
    CharacterBase::Tick(delta_time);
    
    if (input_->IsKeyDown(VK_SPACE))
    {
        rigid_body_->SetVelocity(Math::Vector2::Zero());
        rigid_body_->AddForce(Math::Vector2::Up() * 5.f, ForceMode::kImpulse);
    }
}
