#pragma once
#include "Component.h"

struct ID2D1Bitmap;

class SpriteComponent : public Component
{
public:
    SpriteComponent(class Actor* owner);
    virtual ~SpriteComponent() final = default;

    virtual void Render() final;

private:
    ID2D1Bitmap* sprite_;
    
};
