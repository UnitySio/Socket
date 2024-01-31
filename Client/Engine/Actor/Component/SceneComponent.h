#pragma once
#include <vector>

#include "ActorComponent.h"
#include "box2d/b2_math.h"

class b2World;
class b2Body;

class SceneComponent : public ActorComponent
{
public:
    SceneComponent(class Actor* owner, const std::wstring& name);
    virtual ~SceneComponent() override = default;

    virtual void TickComponent(float delta_time) override;
    virtual void Render() override;

    void SetLocation(const b2Vec2& location);
    void SetRotation(float angle);
    void SetupAttachment(SceneComponent* parent);

    b2Vec2 GetLocation() const { return relative_transform_.p; }
    float GetRotation() const { return relative_transform_.q.GetAngle(); }

    b2World* GetWorld() const;

    b2Body* GetBody() const { return body_; }

private:
    friend class SceneComponent;

    void UpdateTransform();
    
    b2Body* body_;
    
    b2Transform transform_;
    b2Transform relative_transform_;

    SceneComponent* parent_;
    std::vector<SceneComponent*> children_;
    
};
