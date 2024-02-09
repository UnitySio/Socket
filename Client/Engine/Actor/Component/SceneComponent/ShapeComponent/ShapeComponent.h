#pragma once
#include "../SceneComponent.h"

class b2Body;

class ShapeComponent : public SceneComponent
{
public:
    ShapeComponent(Actor* owner, const std::wstring& kName);
    virtual ~ShapeComponent() override = default;

    virtual void SetRelativeLocation(const b2Vec2& location) override;
    virtual void SetRelativeRotation(float angle) override;

    virtual void UpdateTransform() = 0;

protected:
    void CreateFixture(class b2Shape* shape);
    void UpdateChildTransforms();
    
    class b2Fixture* fixture_;
    
};
