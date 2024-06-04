#pragma once

#include "ActorComponent.h"
#include "Math/Vector2.h"

class TransformComponent : public ActorComponent
{
public:
    TransformComponent(class Actor* owner, const std::wstring& kName);
    virtual ~TransformComponent() override = default;

    virtual void TickComponent(float delta_time) override;

    void SetRelativeLocation(Math::Vector2 location);
    void SetRelativeRotationZ(float angle);

    inline void SetRelativeScale(Math::Vector2 scale) { relative_scale_ = scale; }

    Math::Vector2 GetRightVector() const;
    Math::Vector2 GetUpVector() const;

    inline Math::Vector2 GetWorldLocation() const { return world_location_; }
    inline Math::Vector2 GetWorldScale() const { return world_scale_; }
    inline Math::Vector2 GetRelativeLocation() const { return relative_location_; }
    inline Math::Vector2 GetRelativeScale() const { return relative_scale_; }

    inline float GetWorldRotationZ() const { return world_rotation_z_; }
    inline float GetRelativeRotationZ() const { return relative_rotation_z_; }

private:
    friend class Actor;
    friend class ColliderComponent;
    friend class RigidBodyComponent;

    void UpdateTransform();

    Math::Vector2 world_location_;
    Math::Vector2 world_scale_;
    Math::Vector2 relative_location_;
    Math::Vector2 relative_scale_;

    float world_rotation_z_;
    float relative_rotation_z_;
    
};
