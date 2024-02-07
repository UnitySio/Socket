﻿#pragma once
#include "ShapeComponent.h"

class CircleComponent : public ShapeComponent
{
public:
    CircleComponent(Actor* owner, const std::wstring& kName);
    virtual ~CircleComponent() override = default;

    void SetCircleRadius(float radius);

    virtual void UpdateTransform() override;

private:
    float radius_;
    
};