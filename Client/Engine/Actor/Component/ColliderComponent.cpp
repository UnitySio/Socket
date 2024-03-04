#include "ColliderComponent.h"

#include "Actor/Actor.h"
#include "box2d/b2_fixture.h"

ColliderComponent::ColliderComponent(Actor* owner, const std::wstring& kName) :
    ActorComponent(owner, kName),
    fixture_(nullptr),
    offset_(Vector::Zero())
{
}

void ColliderComponent::SetTrigger(bool isTrigger)
{
    if (!fixture_) return;
    fixture_->SetSensor(isTrigger);
}

void ColliderComponent::SetOffset(const Vector& kOffset)
{
    offset_ = kOffset;
}

const Bounds& ColliderComponent::GetBounds()
{
    b2AABB aabb = fixture_->GetAABB(0);

    Bounds bounds;
    bounds.center = {aabb.GetCenter().x, aabb.GetCenter().y};
    bounds.size = {aabb.GetExtents().x * 2.f, aabb.GetExtents().y * 2.f};
    bounds.extents = {aabb.GetExtents().x, aabb.GetExtents().y};
    bounds.min = {aabb.lowerBound.x, aabb.lowerBound.y};
    bounds.max = {aabb.upperBound.x, aabb.upperBound.y};

    return bounds;
}

void ColliderComponent::CreateFixture(b2Shape* shape)
{
    b2FixtureDef fixture_def;
    fixture_def.shape = shape;

    if (fixture_)
    {
        fixture_def.density = fixture_->GetDensity();
        fixture_def.friction = fixture_->GetFriction();
        fixture_def.isSensor = fixture_->IsSensor();

        owner_->body_->DestroyFixture(fixture_);
    }
    else
    {
        fixture_def.density = 1.f;
        fixture_def.friction = 0.3f;
    }

    fixture_ = owner_->body_->CreateFixture(&fixture_def);
}
