#include "pch.h"
#include "Bullet.h"

#include "Actor/Component/CircleColliderComponent.h"
#include "Actor/Component/RigidBody2DComponent.h"

Bullet::Bullet(const std::wstring& kName) :
    Actor(kName)
{
    circle_collider_ = AddComponent<CircleColliderComponent>(L"CircleCollider");
    circle_collider_->SetRadius(.25f);
    circle_collider_->SetTrigger(true);

    rigid_body_ = AddComponent<RigidBody2DComponent>(L"RigidBody");
    rigid_body_->SetCollisionDetectionMode(CollisionDetectionMode::kContinuous);
}

void Bullet::BeginPlay()
{
    Actor::BeginPlay();

    SetActive(false);
}

void Bullet::OnEnable()
{
    Actor::OnEnable();
    
    rigid_body_->AddForceX(10.f, ForceMode::kImpulse);

    TimerManager::Get()->SetTimer(this, &Bullet::Push, 1.f);
}

void Bullet::Pop()
{
    SetActive(true);
}

void Bullet::Push()
{
    SetActive(false);
}

RTTR_REGISTRATION
{
    using namespace rttr;

    registration::class_<Bullet>("Bullet")
        .constructor<const std::wstring&>();
}
