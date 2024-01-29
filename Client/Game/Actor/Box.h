#pragma once

#include "../../Engine/Actor/Actor.h"

class Box : public Actor
{
public:
    Box(b2World* world, const std::wstring& name);
    virtual ~Box() override = default;

    virtual void Render() override;

private:
    class ID2D1Bitmap* texture_;
    
};
