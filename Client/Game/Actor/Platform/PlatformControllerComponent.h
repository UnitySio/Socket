﻿#pragma once
#include "Actor/Component/RayCastController.h"

class PlatformControllerComponent : public RayCastController
{
public:
    PlatformControllerComponent(Actor* owner, const std::wstring& kName);
    virtual ~PlatformControllerComponent() override = default;

    virtual void TickComponent(float delta_time) override;

private:
    void MovePassengers(Math::Vector2 velocity);
    
    Math::Vector2 move_;
    
};
