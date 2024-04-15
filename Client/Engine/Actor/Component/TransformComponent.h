#pragma once

#include "ActorComponent.h"
#include "Math/Vector.h"

class TransformComponent : public ActorComponent
{
public:
    TransformComponent(class Actor* owner, const std::wstring& kName);
    virtual ~TransformComponent() override = default;

    virtual void TickComponent(float delta_time) override;

    void SetRelativeLocation(Math::Vector location);
    void SetRelativeRotationZ(float angle);

    inline void SetRelativeScale(Math::Vector scale) { relative_scale_ = scale; }

    Math::Vector GetRightVector() const;
    Math::Vector GetUpVector() const;

    inline Math::Vector GetWorldLocation() const { return world_location_; }
    inline Math::Vector GetWorldScale() const { return world_scale_; }
    inline Math::Vector GetRelativeLocation() const { return relative_location_; }
    inline Math::Vector GetRelativeScale() const { return relative_scale_; }

    inline float GetWorldRotationZ() const { return world_rotation_z_; }
    inline float GetRelativeRotationZ() const { return relative_rotation_z_; }

private:
    friend class Actor;
    friend class ColliderComponent;
    friend class RigidBodyComponent;

    void UpdateTransform();

    Math::Vector world_location_;
    Math::Vector world_scale_;
    Math::Vector relative_location_;
    Math::Vector relative_scale_;

    float world_rotation_z_;
    float relative_rotation_z_;
    
};
