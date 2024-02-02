#pragma once
#include "../SceneComponent.h"

class b2Body;

class ShapeComponent : public SceneComponent
{
public:
    ShapeComponent(Actor* owner, const std::wstring& kName);
    virtual ~ShapeComponent() override;

    virtual void EndPlay() override;

    inline b2Body* GetBody() const { return body_; }
    
};
