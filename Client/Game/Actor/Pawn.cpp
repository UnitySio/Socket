#include "Pawn.h"

#include "../../Engine/Core.h"
#include "../../Engine/Actor/Component/Scenecomponent/CameraComponent.h"
#include "../../Engine/Actor/Component/BoxColliderComponent.h"
#include "../../Engine/Actor/Component/RigidBodyComponent.h"
#include "../../Engine/Graphics/Graphics.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Level/Level.h"
#include "../../Engine/Vector.h"

Pawn::Pawn(b2World* world, const std::wstring& kName) :
    Actor(world, kName)
{
    camera_view_ = CreateComponent<CameraComponent>(L"Camera");
    SetRootComponent(camera_view_);

    box_collider_ = CreateComponent<BoxColliderComponent>(L"BoxCollider");

    rigid_body_ = CreateComponent<RigidBodyComponent>(L"RigidBody");
    rigid_body_->SetBodyType(BodyType::kDynamic);
    
    SetActorLocation(b2Vec2(0.f, -100.f));
}

void Pawn::Tick(float delta_time)
{
    Actor::Tick(delta_time);

    InputManager* input = InputManager::Get();
    float h = input->IsKeyPressed(VK_RIGHT) - input->IsKeyPressed(VK_LEFT);

    rigid_body_->SetVelocity({h * 100.f, rigid_body_->GetVelocity().y});

    if (input->IsKeyDown(VK_SPACE))
    {
        rigid_body_->AddForce(Vector::Up() * 500000.f, ForceMode::kImpulse);
    }
}
