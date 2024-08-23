#pragma once
#include "ColliderComponent.h"

enum class CapsuleDirection
{
    Horizontal,
    Vertical
};

class CapsuleColliderComponent : public ColliderComponent
{
    SHADER_CLASS_HELPER(CapsuleColliderComponent)
    
public:
    CapsuleColliderComponent(Actor* owner, const std::wstring& kName);
    virtual ~CapsuleColliderComponent() override = default;

    virtual void SetOffset(const Math::Vector2& kOffset) override;

    void SetSize(Math::Vector2 size);
    void SetTrigger(bool is_trigger);

    inline void SetDirection(CapsuleDirection direction) { direction_ = direction; }

private:
    void SetCapsule();

    CapsuleDirection direction_;
    Math::Vector2 size_;
    
};
