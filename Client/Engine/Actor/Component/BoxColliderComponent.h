#pragma once
#include "ColliderComponent.h"

class BoxColliderComponent : public ColliderComponent
{
    SHADER_CLASS_HELPER(BoxColliderComponent)
    
public:
    BoxColliderComponent(Actor* owner, const std::wstring& kName);
    virtual ~BoxColliderComponent() override = default;

    void SetSize(Math::Vector2 size);

private:
    virtual void SetShape() override;
    virtual void SetTriggerInternal() override;
    
    Math::Vector2 size_;
    
};