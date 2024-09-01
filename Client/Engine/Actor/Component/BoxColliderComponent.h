#pragma once
#include "ColliderComponent.h"

class BoxColliderComponent : public ColliderComponent
{
    SHADER_CLASS_HELPER(BoxColliderComponent)
    
public:
    BoxColliderComponent(Actor* owner, const std::wstring& kName);
    virtual ~BoxColliderComponent() override = default;

    virtual void SetOffset(const Math::Vector2& kOffset) override;
    virtual void SetTrigger(bool is_trigger) override;

    void SetSize(Math::Vector2 size);

private:
    virtual void SetShape() override;
    
    Math::Vector2 size_;
    
};
