#pragma once
#include "ShapeComponent.h"

class BoxComponent : public ShapeComponent
{
public:
    BoxComponent(Actor* owner, const std::wstring& kName);
    virtual ~BoxComponent() override = default;

    virtual void SetRelativeLocation(const b2Vec2& location) override;
    virtual void SetRelativeRotation(float angle) override;

    void SetBoxExtent(const b2Vec2& kExtent);

protected:
    void UpdateTransform();

private:
    void CreateFixture(class b2PolygonShape* shape);

    b2Vec2 extent_;
    
};
