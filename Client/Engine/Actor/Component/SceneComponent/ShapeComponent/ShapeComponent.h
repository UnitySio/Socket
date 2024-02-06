#pragma once
#include "../SceneComponent.h"

class b2Body;

class ShapeComponent : public SceneComponent
{
public:
    ShapeComponent(Actor* owner, const std::wstring& kName);
    virtual ~ShapeComponent() override = default;

    virtual void SetupAttachment(SceneComponent* parent) override;

protected:
    class b2Fixture* fixture_;

private:
    class b2Body* CreateBody();
    
};
