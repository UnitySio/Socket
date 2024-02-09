﻿#pragma once
#include <vector>

#include "../ActorComponent.h"
#include "box2d/b2_math.h"

class b2Body;

class SceneComponent : public ActorComponent
{
public:
    SceneComponent(Actor* owner, const std::wstring& kName);
    virtual ~SceneComponent() override = default;

    virtual void Render() override;

    virtual void SetRelativeLocation(const b2Vec2& location);
    virtual void SetRelativeRotation(float angle);
    virtual void SetWorldLocation(const b2Vec2& location);
    virtual void SetWorldRotation(float angle);
    
    void SetupAttachment(SceneComponent* parent);

    void SetRelativeTransform(const b2Transform& transform);
    void SetWorldTransform(const b2Transform& transform);

    inline b2Vec2 GetRelativeLocation() const { return relative_transform_.p; }
    inline b2Vec2 GetWorldLocation() const { return transform_.p; }
    
    inline float GetRelativeRotation() const { return relative_transform_.q.GetAngle(); }
    inline float GetWorldRotation() const { return transform_.q.GetAngle(); }

    inline b2Transform GetWorldTransform() const { return transform_; }
    inline b2Transform GetRelativeTransform() const { return relative_transform_; }

    inline SceneComponent* GetAttachParent() const { return parent_; }
    inline const std::vector<SceneComponent*>& GetAttachChildren() const { return children_; }

protected:
    void UpdateTransform();
    
    b2Transform transform_;
    b2Transform relative_transform_;

    SceneComponent* parent_;
    std::vector<SceneComponent*> children_;
    
};
