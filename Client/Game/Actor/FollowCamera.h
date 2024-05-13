#pragma once
#include "Actor/Actor.h"
#include "Math/Vector2.h"

class FollowCamera : public Actor
{
public:
    FollowCamera(World* world, const std::wstring& kName);
    virtual ~FollowCamera() override = default;

    virtual void Tick(float delta_time) override;

    inline void SetFollow(class Actor* target) { follow_ = target; }
    inline void SetFollowOffset(const Math::Vector2& offset) { follow_offset = offset; }

private:
    class CameraComponent* camera_;
    
    class Actor* follow_;

    float width_;
    float height_;
    float limit_width_;
    float limit_height_;

    Math::Vector2 follow_offset;
    
};
