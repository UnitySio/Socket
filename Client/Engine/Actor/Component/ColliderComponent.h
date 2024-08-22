#pragma once
#include "ActorComponent.h"
#include "box2d/id.h"
#include "Math/Bounds.h"
#include "Math/Vector2.h"

class ColliderComponent : public ActorComponent
{
    SHADER_CLASS_HELPER(ColliderComponent)
    
public:
    ColliderComponent(Actor* owner, const std::wstring& kName);
    virtual ~ColliderComponent() override = default;

    void SetTrigger(bool isTrigger);

    virtual void SetOffset(const Math::Vector2& kOffset);

    const Bounds& GetBounds();

protected:
    b2ShapeId shape_id_;

    Math::Vector2 offset_;
    
};
