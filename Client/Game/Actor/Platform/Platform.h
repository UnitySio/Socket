#pragma once
#include "Actor/Actor.h"

class Platform : public Actor
{
    SHADER_CLASS_HELPER(Platform)
    
public:
    Platform(const std::wstring& kName);
    virtual ~Platform() override = default;

    virtual void Tick(float delta_time) override;

private:
    class BoxColliderComponent* collider_;
    class PlatformControllerComponent* controller_;
    
};
