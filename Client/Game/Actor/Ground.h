#pragma once
#include "../../Engine/Actor/Actor.h"

class Ground : public Actor
{
public:
    Ground(b2World* world);
    virtual ~Ground() final = default;

    virtual void Render() final;
    
};
