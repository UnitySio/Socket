#include "Pawn.h"

#include "Floor.h"
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
    box_collider_->SetSize({32.f, 32.f});

    rigid_body_ = CreateComponent<RigidBodyComponent>(L"RigidBody");
    rigid_body_->SetBodyType(BodyType::kDynamic);
    
    SetActorLocation({0.f, -100.f});
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

void Pawn::OnTriggerEnter(Actor* other)
{
    Actor::OnTriggerEnter(other);

    if (wcscmp(other->GetName().c_str(), L"Floor") == 0)
    {
        Floor* floor = dynamic_cast<Floor*>(other);
        BoxColliderComponent* floor_collider = floor->GetBoxCollider();

        Bounds bounds = box_collider_->GetBounds();
        Bounds floor_bounds = floor_collider->GetBounds();
        Bounds intersect = Bounds::Intersect(bounds, floor_bounds);

        // 디버그 확인을 위한 더비 코드
        int a = 0;
    }
}
