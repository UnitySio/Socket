#include "ShapeComponent.h"

#include "box2d/b2_body.h"
#include "box2d/b2_world.h"

ShapeComponent::ShapeComponent(Actor* owner, const std::wstring& kName) :
    SceneComponent(owner, kName)
{
    const b2Vec2 position = GetRelativeLocation();

    b2BodyDef body_def;
    body_def.position.Set(position.x, position.y);

    body_ = GetWorld()->CreateBody(&body_def);
}

ShapeComponent::~ShapeComponent()
{
    GetWorld()->DestroyBody(body_);
}
