#include "pch.h"
#include "CharacterBase.h"

#include "Actor/Component/SpriteRendererComponent.h"
#include "Actor/Component/Controller2DComponent.h"
#include "Actor/StateMachine/StateMachine.h"

CharacterBase::CharacterBase(const std::wstring& kName) :
    Actor(kName),
    velocity_(Math::Vector2::Zero()),
    gravity_(-9.81f)
{
    state_machine_ = std::make_unique<StateMachine>();
    
    sprite_renderer_ = AddComponent<SpriteRendererComponent>(L"SpriteRenderer");
    capsule_collider_ = AddComponent<CapsuleColliderComponent>(L"CapsuleCollider");
    capsule_collider_->SetSize({.5f, .5f});
    
    controller_ = AddComponent<Controller2DComponent>(L"Controller2D");
    controller_->SetCollider(capsule_collider_);
}

void CharacterBase::Tick(float delta_time)
{
    Actor::Tick(delta_time);

    state_machine_->Tick(delta_time);

    velocity_.y += gravity_ * delta_time;
    controller_->Move(velocity_ * delta_time);

    const CollisionInfo& collisions = controller_->GetCollisions();
    if (collisions.above || collisions.below)
    {
        velocity_.y = 0.f;
    }
}
