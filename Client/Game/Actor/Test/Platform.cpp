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
    box_collider_->SetOneWayPlatform(true);

    rigid_body_ = CreateComponent<RigidBody2DComponent>(L"RigidBody");
    rigid_body_->SetBodyType(BodyType::kKinematic);

    GetTransform()->SetWorldPosition({1.5f, -3.f});
    
}
