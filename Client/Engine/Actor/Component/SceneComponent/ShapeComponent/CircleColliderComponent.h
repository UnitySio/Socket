#pragma once
#include "ColliderComponent.h"

class CircleColliderComponent : public ColliderComponent
{
public:
    CircleColliderComponent(Actor* owner, const std::wstring& kName);
    virtual ~CircleColliderComponent() override = default;

    void SetCircleRadius(float radius);

    virtual void UpdateTransform() override;

private:
    float radius_;
    
};
