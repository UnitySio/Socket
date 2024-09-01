#pragma once

#include "ActorComponent.h"
#include "Math/Vector2.h"

class TransformComponent : public ActorComponent
{
    SHADER_CLASS_HELPER(TransformComponent)
    
public:
    TransformComponent(class Actor* owner, const std::wstring& kName);
    virtual ~TransformComponent() override = default;

    virtual void PhysicsTickComponent(float delta_time) override;

    void SetPosition(const Math::Vector2& position);
    void SetAngle(float angle);
    void SetScale(const Math::Vector2& scale);
    void Translate(const Math::Vector2& translation);

    Math::Vector2 GetRightVector() const;
    Math::Vector2 GetUpVector() const;

    inline Math::Vector2 GetPosition() const { return position_; }
    inline Math::Vector2 GetScale() const { return scale_; }

    inline float GetAngle() const { return angle_; }

private:
    friend class Actor;
    friend class ColliderComponent;
    friend class RigidBody2DComponent;

    Math::Vector2 position_;
    Math::Vector2 scale_;

    float angle_;
    
};
