#pragma once
#include "ActorComponent.h"
#include "Math/Bounds.h"

class CameraComponent : public ActorComponent
{
    DECLARE_SHARED_CLASS(ActorComponent, CameraComponent);
    
public:
    CameraComponent(Actor* owner, const std::wstring& kName);
    virtual ~CameraComponent() override = default;

    virtual void InitializeComponent() override;
    virtual void TickComponent(float delta_time) override;

    void SetSize(float size);
    void SetNearZ(float near_z);
    void SetFarZ(float far_z);

    Bounds GetBounds() const;

    inline float GetSize() const { return size_; }
    inline float GetAspect() const { return aspect_; }

private:
    float size_;
    float near_z_;
    float far_z_;
    float aspect_;

    void UpdateAspect();
    void UpdateProjectionMatrix();
    
};
