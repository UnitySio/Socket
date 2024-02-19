#pragma once
#include "ColliderComponent.h"

class CircleColliderComponent : public ColliderComponent
{
public:
    CircleColliderComponent(Actor* owner, const std::wstring& kName);
    virtual ~CircleColliderComponent() override = default;

    virtual void SetOffset(const Vector& kOffset) override;

    void SetRadius(float radius);

private:
    void SetCircle();
    
    float radius_;
    
};
