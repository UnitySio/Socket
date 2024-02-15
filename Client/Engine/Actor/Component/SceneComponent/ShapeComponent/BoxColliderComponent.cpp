#include "BoxColliderComponent.h"

#include <valarray>

#include "../../../Actor.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"

BoxColliderComponent::BoxColliderComponent(Actor* owner, const std::wstring& kName) :
    ColliderComponent(owner, kName),
    extent_(b2Vec2_zero)
{
}

void BoxColliderComponent::SetBoxExtent(const b2Vec2& kExtent)
{
    extent_ = kExtent;

    b2PolygonShape box;
    box.SetAsBox(extent_.x, extent_.y);

    CreateFixture(&box);
}

void BoxColliderComponent::UpdateTransform()
{
    b2Body* body = owner_->body_;

    b2Vec2 location = body->GetLocalPoint(GetWorldLocation());
    b2Rot rotation = b2MulT(body->GetTransform().q, GetWorldTransform().q);

    b2PolygonShape box;
    box.SetAsBox(extent_.x, extent_.y, location, rotation.GetAngle());

    CreateFixture(&box);
    UpdateChildTransforms();
}
