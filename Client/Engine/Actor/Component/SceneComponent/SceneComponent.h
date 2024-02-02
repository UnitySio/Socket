#pragma once
#include <vector>

#include "../ActorComponent.h"
#include "box2d/b2_math.h"

class SceneComponent : public ActorComponent
{
public:
    SceneComponent(Actor* owner, const std::wstring& kName);
    virtual ~SceneComponent() override = default;

    virtual void Render() override;

    void SetLocation(const b2Vec2& location);
    void SetRotation(float angle);
    void SetupAttachment(SceneComponent* parent);

    inline b2Vec2 GetLocation() const { return relative_transform_.p; }
    inline b2Vec2 GetWorldLocation() const { return transform_.p; }
    
    inline float GetRotation() const { return relative_transform_.q.GetAngle(); }
    inline float GetWorldRotation() const { return transform_.q.GetAngle(); }

    inline b2Transform GetTransform() const { return transform_; }
    inline b2Transform GetRelativeTransform() const { return relative_transform_; }

    inline SceneComponent* GetAttachParent() const { return parent_; }

private:
    friend class SceneComponent;

    void UpdateTransform();
    
    b2Transform transform_;
    b2Transform relative_transform_;

    SceneComponent* parent_;
    std::vector<SceneComponent*> children_;
    
};
