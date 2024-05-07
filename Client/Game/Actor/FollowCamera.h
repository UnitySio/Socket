#pragma once
#include "Actor/Actor.h"

class FollowCamera : public Actor
{
public:
    FollowCamera(World* world, const std::wstring& kName);
    virtual ~FollowCamera() override = default;

    virtual void Tick(float delta_time) override;

    inline void SetFollow(class Actor* target) { follow_ = target; }

private:
    class CameraComponent* camera_;
    
    class Actor* follow_;
    
};
