#include "pch.h"
#include "Bullet.h"

#include "Actor/Component/CircleColliderComponent.h"
#include "Actor/Component/RigidBody2DComponent.h"

Bullet::Bullet(const std::wstring& kName) :
    PooledObject(kName)
{
    circle_collider_ = AddComponent<CircleColliderComponent>(L"CircleCollider");
    circle_collider_->SetRadius(.25f);
    // circle_collider_->SetTrigger(true);
    
    rigid_body_ = AddComponent<RigidBody2DComponent>(L"RigidBody");
    rigid_body_->SetCollisionDetectionMode(CollisionDetectionMode::kContinuous);
}

void Bullet::OnEnable()
{
    PooledObject::OnEnable();

    rigid_body_->AddForceX(20.f, ForceMode::kImpulse);
}

RTTR_REGISTRATION
{
    using namespace rttr;

    registration::class_<Bullet>("Bullet")
        .constructor<const std::wstring&>()
        (
            policy::ctor::as_std_shared_ptr
        );
}
