#include "pch.h"
#include "Bullet.h"

#include "Actor/Component/CircleColliderComponent.h"
#include "Actor/Component/RigidBody2DComponent.h"

Bullet::Bullet(const std::wstring& kName) :
    Actor(kName)
{
    circle_collider_ = AddComponent<CircleColliderComponent>(L"CircleCollider");
    circle_collider_->SetRadius(.5f);

    rigid_body_ = AddComponent<RigidBody2DComponent>(L"RigidBody");
    rigid_body_->SetCollisionDetectionMode(CollisionDetectionMode::kContinuous);
}

void Bullet::BeginPlay()
{
    Actor::BeginPlay();

    SetActive(false);
}

RTTR_REGISTRATION
{
    using namespace rttr;

    registration::class_<Bullet>("Bullet")
        .constructor<const std::wstring&>();
}
