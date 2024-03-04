#include "BoxColliderComponent.h"

#include "box2d/b2_polygon_shape.h"

BoxColliderComponent::BoxColliderComponent(Actor* owner, const std::wstring& kName) :
    ColliderComponent(owner, kName),
    size_(Vector::One())
{
    SetBox();
}

void BoxColliderComponent::SetOffset(const Vector& kOffset)
{
    ColliderComponent::SetOffset(kOffset);
    
    SetBox();
}

void BoxColliderComponent::SetSize(Vector size)
{
    size_ = size;
    SetBox();
}

void BoxColliderComponent::SetBox()
{
    const Vector half_size = size_ * .5f;
    
    b2PolygonShape box;
    box.SetAsBox(half_size.x, half_size.y, {offset_.x, offset_.y}, 0.f);

    CreateFixture(&box);
}
