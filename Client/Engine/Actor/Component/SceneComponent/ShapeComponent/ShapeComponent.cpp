#include "ShapeComponent.h"

#include "../../../Actor.h"
#include "box2d/b2_body.h"
#include "box2d/b2_world.h"

ShapeComponent::ShapeComponent(Actor* owner, const std::wstring& kName) :
    SceneComponent(owner, kName),
    fixture_(nullptr)
{
    body_ = CreateBody();
}

void ShapeComponent::SetupAttachment(SceneComponent* parent)
{
    SceneComponent::SetupAttachment(parent);

    SceneComponent* root = owner_->GetRootComponent();
    assert(root);

    if (!root->GetBody()) root->SetBody(CreateBody());

    GetWorld()->DestroyBody(body_);
    body_ = nullptr;
}

b2Body* ShapeComponent::CreateBody()
{
    const b2Vec2 position = GetRelativeLocation();

    b2BodyDef body_def;
    body_def.userData.pointer = reinterpret_cast<uintptr_t>(owner_);
    body_def.position.Set(position.x, position.y);

    return GetWorld()->CreateBody(&body_def);
}
