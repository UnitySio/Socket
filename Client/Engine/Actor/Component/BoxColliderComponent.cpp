#include "BoxColliderComponent.h"

#include "box2d/b2_polygon_shape.h"

BoxColliderComponent::BoxColliderComponent(Actor* owner, const std::wstring& kName) :
    ColliderComponent(owner, kName),
    size_(Math::Vector2::One())
{
    SetBox();
}

void BoxColliderComponent::SetOffset(const Math::Vector2& kOffset)
{
    ColliderComponent::SetOffset(kOffset);
    
    SetBox();
}

void BoxColliderComponent::SetSize(Math::Vector2 size)
{
    size_ = size;
    SetBox();
}

void BoxColliderComponent::SetBox()
{
    const Math::Vector2 half_size = size_ * .5f;
    
    b2PolygonShape box;
    box.SetAsBox(half_size.x, half_size.y, {offset_.x, offset_.y}, 0.f);

    CreateFixture(&box);
}
