#include "pch.h"
#include "Platform.h"

#include "Actor/Component/SegmentColliderComponent.h"
#include "Actor/Component/RigidBody2DComponent.h"
#include "Actor/Component/TransformComponent.h"

Platform::Platform(const std::wstring& kName) :
    Actor(kName)
{
    segment_collider_ = CreateComponent<SegmentColliderComponent>(L"SegmentCollider");
    segment_collider_->SetSegment({0.f, -3.f}, {6.f, -3.f});
    segment_collider_->SetOneWayPlatform(true);

    rigid_body_ = CreateComponent<RigidBody2DComponent>(L"RigidBody");
    rigid_body_->SetBodyType(BodyType::kKinematic);
    
}
