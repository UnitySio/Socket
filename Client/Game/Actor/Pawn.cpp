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
#include "../../Engine/Level/Level.h"
#include "../../Engine/Vector.h"
#include "../../Engine/Level/LevelManager.h"

Pawn::Pawn(b2World* world, const std::wstring& kName) :
    Actor(world, kName),
    bounds_()
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

void Pawn::Render()
{
    Actor::Render();

    Graphics* graphics = Graphics::Get();
    b2Vec2 position = {bounds_.center.x, bounds_.center.y};
    b2Vec2 size = {bounds_.extents.x * 2.f, bounds_.extents.y * 2.f};

    Level* level = LevelManager::Get()->GetLevel();
    b2Vec2 render_position = level->GetRenderPosition(position);

    graphics->DrawBox(render_position, size, 0.f, {1.f, 0.f, 0.f, 1.f});
}

void Pawn::OnTriggerStay(Actor* other)
{
    Actor::OnTriggerStay(other);

    if (wcscmp(other->GetName().c_str(), L"Dummy") == 0)
    {
        Dummy* dummy = dynamic_cast<Dummy*>(other);
        BoxColliderComponent* floor_collider = dummy->GetBoxCollider();

        Bounds bounds = box_collider_->GetBounds();
        Bounds floor_bounds = floor_collider->GetBounds();
        bounds_ = Bounds::Intersect(bounds, floor_bounds);
    }
}
