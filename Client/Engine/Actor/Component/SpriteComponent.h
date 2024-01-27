#pragma once
#include "ActorComponent.h"

struct ID2D1Bitmap;

class SpriteComponent : public ActorComponent
{
public:
    SpriteComponent(class Actor* owner, const std::wstring& name);
    virtual ~SpriteComponent() override = default;

    virtual void Render() override;

private:
    ID2D1Bitmap* sprite_;
    
};
