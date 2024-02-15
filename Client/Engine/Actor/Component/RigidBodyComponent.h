#pragma once
#include "ActorComponent.h"

class RigidBodyComponent : public ActorComponent
{
public:
    RigidBodyComponent(class Actor* owner, const std::wstring& kName);
    virtual ~RigidBodyComponent() override = default;
    
};
