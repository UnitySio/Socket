#pragma once
#include "ShapeComponent.h"
#include "box2d/b2_math.h"

class CircleComponent : public ShapeComponent
{
public:
    CircleComponent(Actor* owner, const std::wstring& name);
    virtual ~CircleComponent() override = default;

    void SetRadius(float radius, b2Vec2 center = b2Vec2(0.f, 0.f));
    
};
