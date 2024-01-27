#pragma once
#include "ActorComponent.h"

class ShapeComponent : public ActorComponent
{
public:
    ShapeComponent(class Actor* actor, const std::wstring& name);
    virtual ~ShapeComponent() override = default;

    void SetDensity(float density);
    void SetFriction(float friction);
    void SetRestitution(float restitution);
    void SetRestitutionThreshold(float threshold);
    void SetTrigger(bool trigger);

protected:
    class b2Fixture* fixture_;
    
};
