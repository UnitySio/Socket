#include "pch.h"
#include "CharacterBase.h"

#include "Actor/Component/SpriteRendererComponent.h"
#include "Actor/Component/Animator/AnimatorComponent.h"
#include "Actor/Component/CapsuleColliderComponent.h"
#include "Actor/Component/RigidBody2DComponent.h"

CharacterBase::CharacterBase(const std::wstring& kName) :
    StateMachine(kName)
{
    sprite_renderer_ = AddComponent<SpriteRendererComponent>(L"SpriteRenderer");
    animator_ = AddComponent<AnimatorComponent>(L"Animator");

    // PhysicsMaterial2D material = {0.f, 1.f};
    
    capsule_collider_ = AddComponent<CapsuleColliderComponent>(L"CapsuleCollider");
    // capsule_collider_->SetMaterial(material);
    capsule_collider_->SetSize({1.f, 1.f});
    capsule_collider_->SetPreSolve(true);

    rigid_body_ = AddComponent<RigidBody2DComponent>(L"RigidBody");
    rigid_body_->SetBodyType(BodyType::kDynamic);
    rigid_body_->SetFreezeRotation(true);
    rigid_body_->UseAutoMass(false);
    
}
