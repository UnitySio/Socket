#pragma once
#include "../../Engine/Actor/Actor.h"

class JointTest : public Actor
{
public:
    JointTest(class b2World* world, const std::wstring& name);
    virtual ~JointTest() override = default;

    virtual void BeginPlay() override;
    
};
