#pragma once
#include "ShapeComponent.h"
#include "box2d/b2_math.h"

class BoxComponent : public ShapeComponent
{
public:
    BoxComponent(class Actor* actor);
    virtual ~BoxComponent() override = default;

    void SetBox(b2Vec2 size, b2Vec2 center = b2Vec2(0.f, 0.f));
    
};
