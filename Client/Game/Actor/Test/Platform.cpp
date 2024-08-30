#include "pch.h"
#include "Platform.h"

#include "Actor/Component/BoxColliderComponent.h"
#include "Actor/Component/RigidBody2DComponent.h"
#include "Actor/Component/TransformComponent.h"

Platform::Platform(const std::wstring& kName) :
    Actor(kName)
{
    box_collider_ = CreateComponent<BoxColliderComponent>(L"BoxCollider");
    box_collider_->SetSize({ 6.f, 1.f });

    rigid_body_ = CreateComponent<RigidBody2DComponent>(L"RigidBody");
    rigid_body_->SetBodyType(BodyType::kKinematic);
    
}

void Platform::PhysicsTick(float delta_time)
{
    Actor::PhysicsTick(delta_time);

    Math::Vector2 position = GetTransform()->GetWorldPosition();
    
}
