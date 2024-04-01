#pragma once
#include "ActorComponent.h"
#include "Vector.h"

class TransformComponent : public ActorComponent
{
public:
    TransformComponent(class Actor* owner, const std::wstring& kName);
    virtual ~TransformComponent() override = default;

    void SetLocation(Vector location);
    void SetRotation(float angle);

    inline void SetScale(Vector scale) { scale_ = scale; }

    Vector GetLocation() const;
    Vector GetRightVector() const;
    Vector GetUpVector() const;
    
    float GetRotation() const;

    inline Vector GetScale() const { return scale_; }

private:
    friend class ColliderComponent;
    friend class RigidBodyComponent;
    
    class b2Body* body_;

    Vector scale_;
    
};
