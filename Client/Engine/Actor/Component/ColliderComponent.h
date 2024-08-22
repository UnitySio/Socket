#pragma once
#include "ActorComponent.h"
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
    void CreateFixture(class b2Shape* shape);
    
    class b2Fixture* fixture_;

    Math::Vector2 offset_;
    
};
