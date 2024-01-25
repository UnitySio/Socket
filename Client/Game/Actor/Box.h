#pragma once

#include "../../Engine/Actor/Actor.h"

class Box : public Actor
{
public:
    Box(b2World* world);
    virtual ~Box() final = default;
    
    virtual void Render() final;

private:
    class ID2D1Bitmap* texture_;
    
};
