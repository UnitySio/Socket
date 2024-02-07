#include "BoxComponent.h"

#include <valarray>

#include "../../../Actor.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"

BoxComponent::BoxComponent(Actor* owner, const std::wstring& kName) :
    ShapeComponent(owner, kName),
    extent_(b2Vec2_zero)
{
}

void BoxComponent::SetBoxExtent(const b2Vec2& kExtent)
{
    SceneComponent* root = owner_->GetRootComponent();
    assert(root);

    extent_ = kExtent;

    b2PolygonShape box;
    box.SetAsBox(extent_.x, extent_.y);

    CreateFixture(&box);
}

void BoxComponent::UpdateTransform()
{
    SceneComponent* root = owner_->GetRootComponent();
    b2Body* body = root->GetBody();

    b2Vec2 location = body->GetLocalPoint(GetWorldLocation());
    b2Rot rotation = b2MulT(body->GetTransform().q, GetWorldTransform().q);

    b2PolygonShape box;
    box.SetAsBox(extent_.x, extent_.y, location, rotation.GetAngle());

    CreateFixture(&box);
    UpdateChildTransforms();
}
