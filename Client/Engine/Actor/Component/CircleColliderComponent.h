#pragma once
#include "ColliderComponent.h"

class CircleColliderComponent : public ColliderComponent
{
    SHADER_CLASS_HELPER(CircleColliderComponent)
    
public:
    CircleColliderComponent(Actor* owner, const std::wstring& kName);
    virtual ~CircleColliderComponent() override = default;

    virtual void SetOffset(const Math::Vector2& kOffset) override;

    void SetRadius(float radius);

private:
    void SetCircle();
    
    float radius_;
    
};
