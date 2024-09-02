#include "pch.h"
#include "Box.h"

#include "Actor/Component/SpriteRendererComponent.h"
#include "Actor/Component/BoxColliderComponent.h"
#include "Actor/Component/RigidBody2DComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Windows/DX/Shape.h"
#include "Windows/DX/Sprite.h"

Box::Box(const std::wstring& kName) : Actor(kName)
{
    sprite_renderer_ = AddComponent<SpriteRendererComponent>(L"SpriteRenderer");
    
    box_collider_ = AddComponent<BoxColliderComponent>(L"BoxCollider");
    box_collider_->SetSize({1.f, 1.f});

    rigid_body_ = AddComponent<RigidBody2DComponent>(L"RigidBody");
    rigid_body_->SetBodyType(BodyType::kDynamic);
    
    sprite_ = std::make_shared<Sprite>();
    CHECK_IF(sprite_->Load(L".\\Game_Data\\box.png"), L"Failed to load texture");

    sprite_->Split(1, 1, Sprite::kCenter);

    sprite_renderer_->SetSprite(sprite_);

    GetTransform()->SetScale({.125f, .125f});
    
}

void Box::BeginPlay()
{
    Actor::BeginPlay();

    // SetLifeSpan(1.f);
}

void Box::Tick(float delta_time)
{
    Actor::Tick(delta_time);

}
