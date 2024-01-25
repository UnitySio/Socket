#pragma once
#include "Component.h"

class ShapeComponent : public Component
{
public:
    ShapeComponent(class Actor* actor);
    virtual ~ShapeComponent() override = default;

    void SetDensity(float density);
    void SetFriction(float friction);
    void SetRestitution(float restitution);
    void SetRestitutionThreshold(float threshold);
    void SetTrigger(bool trigger);

protected:
    class b2Fixture* fixture_;
    
};
