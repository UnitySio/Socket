#pragma once
#include "Actor/Actor.h"

class Platform : public Actor
{
    SHADER_CLASS_HELPER(Platform);
    
public:
    Platform(const std::wstring& kName);
    virtual ~Platform() override = default;

private:
    class SegmentColliderComponent* segment_collider_;
    class RigidBody2DComponent* rigid_body_;
    
};
