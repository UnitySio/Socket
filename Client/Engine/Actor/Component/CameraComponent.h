#pragma once
#include "ActorComponent.h"

class CameraComponent : public ActorComponent
{
public:
    CameraComponent(Actor* owner, const std::wstring& kName);
    virtual ~CameraComponent() override = default;

    virtual void InitializeComponent() override;
    virtual void TickComponent(float delta_time) override;

    void SetCameraSize(float size);
    void SetCameraNearZ(float near_z);
    void SetCameraFarZ(float far_z);

private:
    float camera_size_;
    float camera_near_z;
    float camera_far_z;

    void UpdateProjectionMatrix();
    
};
