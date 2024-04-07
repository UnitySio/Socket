#pragma once
#include "ActorComponent.h"
#include "Math/Bounds.h"
#include "Math/Vector.h"

class ColliderComponent : public ActorComponent
{
public:
    ColliderComponent(Actor* owner, const std::wstring& kName);
    virtual ~ColliderComponent() override = default;

    void SetTrigger(bool isTrigger);

    virtual void SetOffset(const Vector& kOffset);

    const Bounds& GetBounds();

protected:
    void CreateFixture(class b2Shape* shape);
    
    class b2Fixture* fixture_;

    Vector offset_;
    
};
