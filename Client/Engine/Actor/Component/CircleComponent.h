#pragma once
#include "ShapeComponent.h"

class CircleComponent : public ShapeComponent
{
public:
    CircleComponent(Actor* owner);
    virtual ~CircleComponent() final = default;

    void SetRadius(float radius);
    
};
