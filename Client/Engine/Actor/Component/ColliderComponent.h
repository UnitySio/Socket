#pragma once
#include "ActorComponent.h"

class ColliderComponent : public ActorComponent
{
public:
    ColliderComponent(Actor* owner, const std::wstring& kName);
    virtual ~ColliderComponent() override = default;

protected:
    class b2Fixture* fixture_;
    
};
