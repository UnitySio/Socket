#include "pch.h"
#include "Capsule.h"

#include "Actor/Component/SpriteRendererComponent.h"
#include "Actor/Component/CapsuleColliderComponent.h"
#include "Actor/Component/RigidBody2DComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Resource/ResourceManager.h"
#include "rttr/registration.h"
#include "Windows/DX/Shape.h"
#include "Windows/DX/Sprite.h"

Capsule::Capsule(const std::wstring& kName) : Actor(kName)
{
    SetLayer(ActorLayer::kGround);
    
    sprite_renderer_ = AddComponent<SpriteRendererComponent>(L"SpriteRenderer");

    PhysicsMaterial2D material = {.3f, 1.f};
    
    capsule_collider_ = AddComponent<CapsuleColliderComponent>(L"CapsuleCollider");
    capsule_collider_->SetSize({1.f, 1.f});
    capsule_collider_->SetMaterial(material);

    rigid_body_ = AddComponent<RigidBody2DComponent>(L"RigidBody");
    rigid_body_->SetBodyType(BodyType::kDynamic);
    
    if (ResourceManager::Get()->Load<Sprite>(L"Capsule", L".\\Game_Data\\Default\\Capsule.png"))
    {
        sprite_ = ResourceManager::Get()->GetResource<Sprite>(L"Capsule");
        sprite_->SetPPU(256);
    }

    sprite_->Split(1, 1, Sprite::kCenter);
    sprite_->SetFilterMode(FilterMode::kBilinear);

    sprite_renderer_->SetSprite(sprite_);

    GetTransform()->SetScale({1.f, 1.f});
    
}

void Capsule::BeginPlay()
{
    Actor::BeginPlay();

    // SetLifeSpan(1.f);
}

void Capsule::Tick(float delta_time)
{
    Actor::Tick(delta_time);

}

RTTR_REGISTRATION
{
    using namespace rttr;

    registration::class_<Capsule>(L"Capsule")
        .constructor<const std::wstring&>();
}
