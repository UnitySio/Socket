#pragma once
#include "ColliderComponent.h"

class BoxColliderComponent : public ColliderComponent
{
public:
    BoxColliderComponent(Actor* owner, const std::wstring& kName);
    virtual ~BoxColliderComponent() override = default;

    void SetBoxExtent(const b2Vec2& kExtent);
    
    virtual void UpdateTransform() override;

private:
    b2Vec2 extent_;
    
};
