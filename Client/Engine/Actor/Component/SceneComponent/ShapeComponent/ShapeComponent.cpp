#include "ShapeComponent.h"

#include "box2d/b2_body.h"
#include "box2d/b2_world.h"

ShapeComponent::ShapeComponent(Actor* owner, const std::wstring& kName) :
    SceneComponent(owner, kName),
    body_(nullptr)
{
    const b2Vec2 position = GetLocation();

    b2BodyDef body_def;
    body_def.position.Set(position.x, position.y);

    body_ = GetWorld()->CreateBody(&body_def);
}

ShapeComponent::~ShapeComponent()
{
    GetWorld()->DestroyBody(body_);
}

void ShapeComponent::TickComponent(float delta_time)
{
    SceneComponent::TickComponent(delta_time);

    if (GetAttachParent())
    {
        if (body_->GetType() != b2_staticBody)
        {
            b2Vec2 relative_location = body_->GetPosition() - GetAttachParent()->GetWorldLocation();
            b2Vec2 location = b2MulT(GetAttachParent()->GetTransform().q, relative_location);

            b2Rot relative_rotation(body_->GetAngle());
            b2Rot rotation = b2MulT(GetAttachParent()->GetTransform().q, relative_rotation);
            
            SetLocation(location);
            SetRotation(rotation.GetAngle());
            return;
        }

        body_->SetTransform(GetWorldLocation(), GetWorldRotation());
    }
    else
    {
        SetLocation(body_->GetPosition());
        SetRotation(body_->GetAngle());
    }
}
