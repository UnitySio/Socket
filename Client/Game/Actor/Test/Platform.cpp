#include "pch.h"
#include "Platform.h"

#include "Actor/Component/BoxColliderComponent.h"
#include "Actor/Component/RigidBody2DComponent.h"

Platform::Platform(const std::wstring& kName) :
    Actor(kName)
{
    segment_collider_ = AddComponent<BoxColliderComponent>(L"BoxCollider");
    segment_collider_->SetSize({4.f, 1.f});
    segment_collider_->SetOneWayPlatform(true);

    rigid_body_ = AddComponent<RigidBody2DComponent>(L"RigidBody");
    rigid_body_->SetBodyType(BodyType::kKinematic);
    
}
