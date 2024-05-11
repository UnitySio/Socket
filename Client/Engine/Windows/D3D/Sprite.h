#pragma once
#include <map>

#include "Shape.h"

struct SpriteFrame
{
};

class Sprite : public Shape
{
public:
    Sprite();
    virtual ~Sprite() override = default;

    void AddSprite();

private:
    std::map<std::wstring, SpriteFrame> sprite_frames_;
    
};
