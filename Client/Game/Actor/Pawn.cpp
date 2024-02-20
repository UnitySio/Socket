#include "Pawn.h"

#include <iostream>
#include <ostream>

#include "Dummy.h"
#include "Floor.h"
#include "../../Engine/Core.h"
#include "../../Engine/Actor/Component/Scenecomponent/CameraComponent.h"
#include "../../Engine/Actor/Component/BoxColliderComponent.h"
#include "../../Engine/Actor/Component/RigidBodyComponent.h"
#include "../../Engine/Graphics/Graphics.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Vector.h"

Pawn::Pawn(b2World* world, const std::wstring& kName) :
    Actor(world, kName)
{
    camera_view_ = CreateComponent<CameraComponent>(L"Camera");
    SetRootComponent(camera_view_);

    box_collider_ = CreateComponent<BoxColliderComponent>(L"BoxCollider");
    box_collider_->SetSize({32.f, 32.f});

    rigid_body_ = CreateComponent<RigidBodyComponent>(L"RigidBody");
    rigid_body_->SetBodyType(BodyType::kDynamic);
    rigid_body_->SetSleepMode(SleepMode::kStartAwake);
    
    SetActorLocation({0.f, -100.f});
}

void Pawn::Tick(float delta_time)
{
    Actor::Tick(delta_time);

    InputManager* input = InputManager::Get();
    float h = input->IsKeyPressed(VK_RIGHT) - input->IsKeyPressed(VK_LEFT);
    float v = input->IsKeyPressed(VK_DOWN) - input->IsKeyPressed(VK_UP);

    rigid_body_->SetVelocity({h * 100.f, v * 100.f});

    if (input->IsKeyDown(VK_SPACE))
    {
        rigid_body_->AddForce(Vector::Up() * 500000.f, ForceMode::kImpulse);
    }
}
