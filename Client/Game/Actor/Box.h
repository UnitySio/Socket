#pragma once

#include "../../Engine/Actor/Actor.h"

class Box : public Actor
{
public:
    Box(b2World* world, const std::wstring& name);
    virtual ~Box() override = default;
    
};
