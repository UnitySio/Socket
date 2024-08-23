#pragma once
#include "ColliderComponent.h"

class CapsuleColliderComponent : public ColliderComponent
{
    SHADER_CLASS_HELPER(CapsuleColliderComponent)
    
public:
    CapsuleColliderComponent(Actor* owner, const std::wstring& kName);
    virtual ~CapsuleColliderComponent() override = default;

    virtual void SetOffset(const Math::Vector2& kOffset) override;

    void SetSize(Math::Vector2 size);
    void SetTrigger(bool is_trigger);

private:
    void SetCapsule();
    
    Math::Vector2 size_;
    
};
