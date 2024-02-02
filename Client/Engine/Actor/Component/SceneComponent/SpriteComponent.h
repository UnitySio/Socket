#pragma once
#include "SceneComponent.h"

class SpriteComponent : public SceneComponent
{
public:
    SpriteComponent(Actor* owner, const std::wstring& kName);
    virtual ~SpriteComponent() override = default;
    
};
