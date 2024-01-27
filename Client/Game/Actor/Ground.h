#pragma once
#include "../../Engine/Actor/Actor.h"

class Ground : public Actor
{
public:
    Ground(b2World* world, const std::wstring& name);
    virtual ~Ground() override = default;
    
};
