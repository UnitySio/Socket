#pragma once
#include "Actor.h"
#include "Math/Bounds.h"

class Camera : public Actor
{
    SHADER_CLASS_HELPER(Camera)
    
public:
    Camera(const std::wstring& kName);
    virtual ~Camera() override = default;

    virtual void BeginPlay() override;
    virtual void PhysicsTick(float delta_time) override;

    static Camera* Get();

    void SetSize(float size);
    void SetNearZ(float near_z);
    void SetFarZ(float far_z);

    float GetAspect() const;

    Bounds GetBounds() const;

    inline void SetTarget(Actor* target) { target_ = target; }

    inline float GetSize() const { return size_; }
    inline float GetNearZ() const { return near_z_; }
    inline float GetFarZ() const { return far_z_; }

private:
    void UpdateProjectionMatrix() const;
    
    static std::weak_ptr<Camera> camera_;
    
    float size_;
    float near_z_;
    float far_z_;

    Actor* target_;
    
};
