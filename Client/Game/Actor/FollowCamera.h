#pragma once
#include "../../Engine/Actor/Actor.h"

class FollowCamera : public Actor
{
public:
    FollowCamera(b2World* world, const std::wstring& kName);
    virtual ~FollowCamera() override = default;

    virtual void Tick(float delta_time) override;

    inline class Actor* GetTarget() const { return target_; }
    inline void SetTarget(class Actor* target) { target_ = target; }

private:
    class CameraComponent* camera_;

    class Actor* target_;
    
};
