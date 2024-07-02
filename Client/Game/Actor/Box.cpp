#include "Box.h"

#include "Actor/Component/BoxColliderComponent.h"
#include "Actor/Component/RigidBodyComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Level/World.h"
#include "Windows/DX/Shape.h"
#include "Windows/DX/Sprite.h"

Box::Box(const std::wstring& kName) : Actor(kName)
{
    box_collider_ = CreateComponent<BoxColliderComponent>(L"BoxCollider");
    box_collider_->SetSize({1.f, 1.f});

    rigid_body_ = CreateComponent<RigidBodyComponent>(L"RigidBody");
    rigid_body_->SetBodyType(BodyType::kDynamic);
    
    sprite_ = MAKE_SHARED<Sprite>();
    CHECK_IF(sprite_->Load(L".\\Game_Data\\box.png"), L"Failed to load texture");

    sprite_->Split(1, 1, {.5f, .5f});
    
}

void Box::Render(float alpha)
{
    Actor::Render(alpha);
    
    const std::vector<SpriteFrame>& frames = sprite_->GetFrames();

    const float width = (sprite_->GetWidth() * frames[0].uv_scale.x / sprite_->GetPPU()) * .125f;
    const float height = (sprite_->GetHeight() * frames[0].uv_scale.y / sprite_->GetPPU()) * .125f;
    const float pivot_x = width * frames[0].pivot.x;
    const float pivot_y = height * frames[0].pivot.y;

    SHARED_PTR<Shape> shape = MAKE_SHARED<Shape>();
    shape->SetVertices(sprite_->GetVertices());
    shape->SetIndices(sprite_->GetIndices());
    shape->SetTexture(sprite_);
    shape->SetPosition(GetTransform()->GetWorldPosition());
    shape->SetRotation(GetTransform()->GetWorldRotationZ());
    shape->SetScale({width, height});
    shape->SetUVOffset(frames[0].uv_offset);
    shape->SetUVScale(frames[0].uv_scale);
    shape->SetPivot({pivot_x, pivot_y});
    shape->SetZOrder(1);

    World::Get()->AddShape(shape);
}
