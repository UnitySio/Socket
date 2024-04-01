#pragma once
#include "ActorComponent.h"

class CameraComponent : public ActorComponent
{
public:
    CameraComponent(Actor* owner, const std::wstring& kName);
    virtual ~CameraComponent() override = default;

    virtual void TickComponent(float delta_time) override;
    
};
