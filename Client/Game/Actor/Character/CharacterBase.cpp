#include "pch.h"
#include "CharacterBase.h"

#include "Actor/Component/SpriteRendererComponent.h"
#include "Actor/Component/Animator/AnimatorComponent.h"
#include "Actor/Component/BoxColliderComponent.h"
#include "Actor/Component/RigidBodyComponent.h"

CharacterBase::CharacterBase(const std::wstring& kName) :
    Actor(kName)
{
    sprite_renderer_ = CreateComponent<SpriteRendererComponent>(L"SpriteRenderer");
    animator_ = CreateComponent<AnimatorComponent>(L"Animator");
    
    box_collider_ = CreateComponent<BoxColliderComponent>(L"BoxCollider");
    box_collider_->SetSize({1.f, 1.f});

    rigid_body_ = CreateComponent<RigidBodyComponent>(L"RigidBody");
    rigid_body_->SetBodyType(BodyType::kDynamic);
    rigid_body_->SetFreezeRotation(true);
    
}
