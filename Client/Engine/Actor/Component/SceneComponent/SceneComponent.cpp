#include "SceneComponent.h"

SceneComponent::SceneComponent(Actor* owner, const std::wstring& kName) :
    ActorComponent(owner, kName),
    world_transform_(),
    relative_transform_(),
    parent_(nullptr),
    children_()
{
    relative_transform_.SetIdentity();
    world_transform_ = relative_transform_;
}

void SceneComponent::Render()
{
    ActorComponent::Render();

    // Level* level = LevelManager::Get()->GetLevel();
    // Graphics* graphics = Graphics::Get();
    //
    // graphics->DrawSolidCircle(level->GetRenderPosition(world_transform_.p), 8.f, b2Color(1.f, 1.f, 1.f));
    //
    // const float axis_scale = 16.f;
    // b2Color red(1.f, 0.f, 0.f);
    // b2Color green(0.f, 1.f, 0.f);
    // b2Vec2 p1 = level->GetRenderPosition(world_transform_.p), p2;
    //
    // p2 = p1 + axis_scale * world_transform_.q.GetXAxis();
    // graphics->DrawLine(p1, p2, red);
    //
    // p2 = p1 + axis_scale * world_transform_.q.GetYAxis();
    // graphics->DrawLine(p1, p2, green);
    //
    // for (auto& child : children_)
    // {
    //     graphics->DrawLine(level->GetRenderPosition(world_transform_.p), level->GetRenderPosition(child->world_transform_.p), b2Color(1.f, 1.f, 1.f));
    // }
}

void SceneComponent::SetRelativeLocation(const b2Vec2& location)
{
    // Root Component는 위치를 변경할 수 없음
    // if (owner_->root_component_ == this) return;
    
    relative_transform_.p = location;
    UpdateTransform();
}

void SceneComponent::SetRelativeRotation(float angle)
{
    // Root Component는 회전을 변경할 수 없음
    // if (owner_->root_component_ == this) return;
    
    angle = angle * b2_pi / 180.f;
    relative_transform_.q.Set(angle);
    UpdateTransform();
}

void SceneComponent::SetWorldLocation(const b2Vec2& location)
{
}

void SceneComponent::SetWorldRotation(float angle)
{
}

void SceneComponent::SetupAttachment(SceneComponent* parent)
{
    parent_ = parent;
    parent_->children_.push_back(this);
}

void SceneComponent::SetRelativeTransform(const b2Transform& transform)
{
    relative_transform_ = transform;
    UpdateTransform();
}

void SceneComponent::SetWorldTransform(const b2Transform& transform)
{
}

Vector SceneComponent::GetRelativeLocation() const
{
    b2Vec2 location = relative_transform_.p;
    return {location.x, location.y};
}

Vector SceneComponent::GetWorldLocation() const
{
    b2Vec2 location = world_transform_.p;
    return {location.x, location.y};
}

Transform SceneComponent::GetWorldTransform() const
{
    Transform world_transform;
    world_transform.position = {world_transform_.p.x, world_transform_.p.y};
    world_transform.angle = world_transform_.q.GetAngle() * 180.f / b2_pi;

    return world_transform;
}

Transform SceneComponent::GetRelativeTransform() const
{
    Transform relative_transform;
    relative_transform.position = {relative_transform_.p.x, relative_transform_.p.y};
    relative_transform.angle = relative_transform_.q.GetAngle() * 180.f / b2_pi;

    return relative_transform;
}

void SceneComponent::UpdateTransform()
{
    if (parent_)
    {
        const b2Vec2 parent_location = parent_->world_transform_.p;
        const b2Rot parent_rotation = parent_->world_transform_.q;
        const b2Vec2 location = relative_transform_.p;
        const b2Rot rotation = relative_transform_.q;

        world_transform_.p = parent_location + b2Mul(parent_rotation, location);
        world_transform_.q = b2Mul(parent_rotation, rotation);
    }
    else world_transform_ = relative_transform_; // Root Component

    for (auto& child : children_)
    {
        child->UpdateTransform();
    }
}
