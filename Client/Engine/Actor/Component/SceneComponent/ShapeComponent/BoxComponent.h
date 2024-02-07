#pragma once
#include "ShapeComponent.h"

class BoxComponent : public ShapeComponent
{
public:
    BoxComponent(Actor* owner, const std::wstring& kName);
    virtual ~BoxComponent() override = default;

    void SetBoxExtent(const b2Vec2& kExtent);
    
    virtual void UpdateTransform() override;

private:
    b2Vec2 extent_;
    
};
