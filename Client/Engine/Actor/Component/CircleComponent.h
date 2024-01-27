#pragma once
#include "ShapeComponent.h"

class CircleComponent : public ShapeComponent
{
public:
    CircleComponent(Actor* owner, const std::wstring& name);
    virtual ~CircleComponent() override = default;

    void SetRadius(float radius);
    
};
