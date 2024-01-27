#pragma once
#include "ActorComponent.h"

class CameraComponent : public ActorComponent
{
public:
    CameraComponent(class Actor* owner, const std::wstring& name);
    virtual ~CameraComponent() override = default;

    virtual void TickComponent(float delta_time) override;
    
};
