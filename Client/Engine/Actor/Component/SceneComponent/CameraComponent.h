#pragma once
#include "SceneComponent.h"

class CameraComponent : public SceneComponent
{
public:
    CameraComponent(Actor* owner, const std::wstring& kName);
    virtual ~CameraComponent() override = default;

    virtual void TickComponent(float delta_time) override;
    
};
