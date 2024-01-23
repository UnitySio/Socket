﻿#pragma once
#include "../../Engine/Actor/Actor.h"

class Ground : public Actor
{
public:
    Ground(b2World* world);
    virtual ~Ground() = default;

    virtual void Begin() final;
    virtual void Tick(float deltaTime) final;
    virtual void Render() final;
    
};
