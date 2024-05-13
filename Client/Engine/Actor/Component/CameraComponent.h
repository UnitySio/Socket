#pragma once
#include "ActorComponent.h"

class CameraComponent : public ActorComponent
{
public:
    CameraComponent(Actor* owner, const std::wstring& kName);
    virtual ~CameraComponent() override = default;

    virtual void InitializeComponent() override;
    virtual void TickComponent(float delta_time) override;

    void SetSize(float size);
    void SetNearZ(float near_z);
    void SetFarZ(float far_z);

    inline float GetSize() const { return size_; }
    inline float GetAspect() const { return aspect_; }

private:
    float size_;
    float near_z;
    float far_z_;
    float aspect_;

    void UpdateAspect();
    void UpdateProjectionMatrix();
    
};
