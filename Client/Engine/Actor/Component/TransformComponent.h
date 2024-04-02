#pragma once
#include "ActorComponent.h"
#include "Vector.h"

#define GE_PI 3.14159265358979323846f

class TransformComponent : public ActorComponent
{
public:
    TransformComponent(class Actor* owner, const std::wstring& kName);
    virtual ~TransformComponent() override = default;

    virtual void TickComponent(float delta_time) override;

    void SetRelativeLocation(Vector location);
    void SetRelativeRotationZ(float angle);

    inline void SetRelativeScale(Vector scale) { relative_scale_ = scale; }

    Vector GetRightVector() const;
    Vector GetUpVector() const;

    inline Vector GetWorldLocation() const { return world_location_; }
    inline Vector GetWorldScale() const { return world_scale_; }
    inline Vector GetRelativeLocation() const { return relative_location_; }
    inline Vector GetRelativeScale() const { return relative_scale_; }

    inline float GetWorldRotationZ() const { return world_rotation_z_; }
    inline float GetRelativeRotationZ() const { return relative_rotation_z_; }

private:
    friend class Actor;
    friend class ColliderComponent;
    friend class RigidBodyComponent;

    void UpdateTransform();

    Vector world_location_;
    Vector world_scale_;
    Vector relative_location_;
    Vector relative_scale_;

    float world_rotation_z_;
    float relative_rotation_z_;
    
};
