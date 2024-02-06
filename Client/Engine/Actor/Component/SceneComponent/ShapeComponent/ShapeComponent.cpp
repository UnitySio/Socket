#include "ShapeComponent.h"

#include "box2d/b2_body.h"
#include "box2d/b2_world.h"

ShapeComponent::ShapeComponent(Actor* owner, const std::wstring& kName) :
    SceneComponent(owner, kName),
    fixture_(nullptr)
{
    const b2Vec2 position = GetRelativeLocation();

    b2BodyDef body_def;
    body_def.userData.pointer = reinterpret_cast<uintptr_t>(GetOwner());
    body_def.position.Set(position.x, position.y);

    body_ = GetWorld()->CreateBody(&body_def);
}

void ShapeComponent::EndPlay()
{
    SceneComponent::EndPlay();

    if (body_)
    {
        SetBodyNullptr(GetAttachChildren());
        
        GetWorld()->DestroyBody(body_);
        body_ = nullptr;
    }
}

void ShapeComponent::SetupAttachment(SceneComponent* parent)
{
    SceneComponent::SetupAttachment(parent);
    
    SceneComponent* body_component = GetBodyComponent();
    if (body_component)
    {
        GetWorld()->DestroyBody(body_);
        body_ = body_component->GetBody();
    }
}

void ShapeComponent::SetBodyNullptr(const std::vector<SceneComponent*>& kChildren)
{
    for (auto& child : kChildren)
    {
        if (child->GetBody()) child->SetBody(nullptr);
        SetBodyNullptr(child->GetAttachChildren());
    }
}
