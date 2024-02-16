#pragma once
#include "ColliderComponent.h"

class BoxColliderComponent : public ColliderComponent
{
public:
    BoxColliderComponent(Actor* owner, const std::wstring& kName);
    virtual ~BoxColliderComponent() override = default;
    
};
