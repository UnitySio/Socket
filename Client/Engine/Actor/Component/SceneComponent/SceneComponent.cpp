#include "SceneComponent.h"

#include "../../Actor.h"
#include "../../../Graphics/Graphics.h"
#include "../../../Scene/Level.h"
#include "../../../Scene/SceneManager.h"
#include "box2d/b2_body.h"
#include "box2d/b2_draw.h"

SceneComponent::SceneComponent(Actor* owner, const std::wstring& kName) :
    ActorComponent(owner, kName),
    body_(nullptr),
    transform_(),
    relative_transform_(),
    parent_(nullptr),
    children_()
{
    relative_transform_.SetIdentity();
    transform_ = relative_transform_;
}

void SceneComponent::TickComponent(float delta_time)
{
    ActorComponent::TickComponent(delta_time);

    if (body_)
    {
        if (GetAttachParent())
        {
            if (body_->GetType() != b2_staticBody)
            {
                b2Vec2 relative_location = body_->GetPosition() - GetAttachParent()->GetWorldLocation();
                b2Vec2 location = b2MulT(GetAttachParent()->GetWorldTransform().q, relative_location);

                b2Rot relative_rotation(body_->GetAngle());
                b2Rot rotation = b2MulT(GetAttachParent()->GetWorldTransform().q, relative_rotation);

                relative_transform_.p = location;
                relative_transform_.q = rotation;

                UpdateTransform();
                return;
            }

            body_->SetTransform(GetWorldLocation(), GetWorldRotation());
        }
        else
        {
            relative_transform_.p = body_->GetPosition();
            relative_transform_.q.Set(body_->GetAngle());
            
            UpdateTransform();
        }
    }
}

void SceneComponent::Render()
{
    ActorComponent::Render();

    Level* level = SceneManager::GetInstance()->GetLevel();
    Graphics* graphics = Graphics::GetInstance();

    graphics->DrawSolidCircle(level->GetRenderPosition(transform_.p), 8.f, b2Color(1.f, 1.f, 1.f));
    
    const float axis_scale = 16.f;
    b2Color red(1.f, 0.f, 0.f);
    b2Color green(0.f, 1.f, 0.f);
    b2Vec2 p1 = level->GetRenderPosition(transform_.p), p2;

    p2 = p1 + axis_scale * transform_.q.GetXAxis();
    graphics->DrawLine(p1, p2, red);

    p2 = p1 + axis_scale * transform_.q.GetYAxis();
    graphics->DrawLine(p1, p2, green);

    for (SceneComponent* child : children_)
    {
        graphics->DrawLine(p1, level->GetRenderPosition(child->transform_.p), b2Color(1.f, 1.f, 1.f));
    }
}

void SceneComponent::SetRelativeLocation(const b2Vec2& location)
{
    relative_transform_.p = location;

    if (body_)
    {
        if (parent_)
        {
            const b2Vec2 parent_position = parent_->GetWorldLocation();
            const b2Vec2 world_location = parent_position + b2Mul(parent_->GetWorldTransform().q, location);
            body_->SetTransform(world_location, body_->GetAngle());
        }
        else
        {
            body_->SetTransform(location, body_->GetAngle());
        }
    }
    
    UpdateTransform();
}

void SceneComponent::SetRelativeRotation(float angle)
{
    relative_transform_.q.Set(angle);

    if (body_)
    {
        if (parent_)
        {
            const b2Rot rotation(angle);
            const b2Rot parent_rotation = parent_->GetWorldTransform().q;
            body_->SetTransform(parent_->GetWorldLocation() + b2Mul(parent_rotation, relative_transform_.p), angle);
        }
        else
        {
            body_->SetTransform(body_->GetPosition(), angle);
        }
    }
    
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

void SceneComponent::UpdateTransform()
{
    if (parent_)
    {
        const b2Vec2 parent_location = parent_->transform_.p;
        const b2Rot parent_rotation = parent_->transform_.q;
        const b2Vec2 location = relative_transform_.p;
        const b2Rot rotation = relative_transform_.q;

        transform_.p = parent_location + b2Mul(parent_rotation, location);
        transform_.q = b2Mul(parent_rotation, rotation);
    }
    else transform_ = relative_transform_; // Root Component

    for (SceneComponent* child : children_)
    {
        child->UpdateTransform();
    }
}
