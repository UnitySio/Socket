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

private:
    void UpdateTransform();

    b2Vec2 extent_;
    
};
