#pragma once
#include <vector>

#include "../ActorComponent.h"
#include "../../../Transform.h"
#include "../../../Vector.h"
#include "box2d/b2_math.h"

class b2Body;

class SceneComponent : public ActorComponent
{
public:
    SceneComponent(Actor* owner, const std::wstring& kName);
    virtual ~SceneComponent() override = default;

    virtual void Render() override;

    void SetRelativeLocation(const b2Vec2& location);
    void SetRelativeRotation(float angle);
    void SetWorldLocation(const b2Vec2& location);
    void SetWorldRotation(float angle);
    void SetupAttachment(SceneComponent* parent);
    void SetRelativeTransform(const b2Transform& transform);
    void SetWorldTransform(const b2Transform& transform);

    Vector GetRelativeLocation() const;
    Vector GetWorldLocation() const;
    
    Transform GetWorldTransform() const;
    Transform GetRelativeTransform() const;
    
    inline float GetRelativeRotation() const { return GetRelativeTransform().angle; }
    inline float GetWorldRotation() const { return GetWorldTransform().angle; }

    inline SceneComponent* GetAttachParent() const { return parent_; }
    inline const std::vector<SceneComponent*>& GetAttachChildren() const { return children_; }

protected:
    void UpdateTransform();
    
    b2Transform world_transform_;
    b2Transform relative_transform_;

    SceneComponent* parent_;
    std::vector<SceneComponent*> children_;
    
};
