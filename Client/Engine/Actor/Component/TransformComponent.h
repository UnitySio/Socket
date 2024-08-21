#pragma once

#include "ActorComponent.h"
#include "Math/Vector2.h"

class TransformComponent : public ActorComponent
{
    DECLARE_SHARED_CLASS(ActorComponent, TransformComponent)
    
public:
    TransformComponent(class Actor* owner, const std::wstring& kName);
    virtual ~TransformComponent() override = default;

    virtual void TickComponent(float delta_time) override;

    void SetWorldPosition(Math::Vector2 position);
    void SetWorldRotationZ(float angle);
    void SetWorldScale(Math::Vector2 scale);
    void SetRelativePosition(Math::Vector2 position);
    void SetRelativeRotationZ(float angle);
    void SetRelativeScale(Math::Vector2 scale);

    Math::Vector2 GetRightVector() const;
    Math::Vector2 GetUpVector() const;

    inline Math::Vector2 GetWorldPosition() const { return world_position_; }
    inline Math::Vector2 GetWorldScale() const { return world_scale_; }
    inline Math::Vector2 GetRelativePosition() const { return relative_position_; }
    inline Math::Vector2 GetRelativeScale() const { return relative_scale_; }

    inline float GetWorldRotationZ() const { return world_rotation_z_; }
    inline float GetRelativeRotationZ() const { return relative_rotation_z_; }

private:
    friend class Actor;
    friend class ColliderComponent;
    friend class RigidBodyComponent;

    void UpdateTransform();

    Math::Vector2 world_position_;
    Math::Vector2 world_scale_;
    Math::Vector2 relative_position_;
    Math::Vector2 relative_scale_;

    float world_rotation_z_;
    float relative_rotation_z_;
    
};
