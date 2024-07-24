#include "pch.h"
#include "ColliderComponent.h"

#include "TransformComponent.h"
#include "Actor/Actor.h"
#include "box2d/b2_fixture.h"

ColliderComponent::ColliderComponent(Actor* owner, const std::wstring& kName) :
    ActorComponent(owner, kName),
    fixture_(nullptr),
    offset_(Math::Vector2::Zero())
{
    if (!GetOwner()->body_) GetOwner()->CreateBody();
}

void ColliderComponent::SetTrigger(bool isTrigger)
{
    if (!fixture_) return;
    fixture_->SetSensor(isTrigger);
}

void ColliderComponent::SetOffset(const Math::Vector2& kOffset)
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
        fixture_def.filter = fixture_->GetFilterData();

        GetOwner()->body_->DestroyFixture(fixture_);
    }
    else
    {
        b2Filter filter;
        filter.categoryBits = GetOwner()->GetLayer();
        filter.maskBits = ProjectSettings::kLayerCollisionMatrix.at(GetOwner()->GetLayer());
        
        fixture_def.density = 1.f;
        fixture_def.friction = .3f;
        fixture_def.filter = filter;
    }

    fixture_ = GetOwner()->body_->CreateFixture(&fixture_def);
}
