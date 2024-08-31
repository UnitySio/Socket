#pragma once
#include "ColliderComponent.h"

class SegmentColliderComponent : public ColliderComponent
{
    SHADER_CLASS_HELPER(SegmentColliderComponent)
    
public:
    SegmentColliderComponent(Actor* actor, const std::wstring& kName);

    void SetSegment(const Math::Vector2& start, const Math::Vector2& end);
    void SetTrigger(bool is_trigger);

private:
    virtual void SetShape() override;

    Math::Vector2 start_;
    Math::Vector2 end_;
    
};
