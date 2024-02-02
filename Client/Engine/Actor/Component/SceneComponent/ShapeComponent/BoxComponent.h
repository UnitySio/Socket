#pragma once
#include "ShapeComponent.h"

class BoxComponent : public ShapeComponent
{
public:
    BoxComponent(Actor* owner, const std::wstring& kName);
    virtual ~BoxComponent() override = default;

    void SetBoxExtent(const b2Vec2& kExtent);

private:
    class b2Fixture* fixture_;
    
};
