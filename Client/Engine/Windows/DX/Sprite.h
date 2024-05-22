#pragma once
#include <map>
#include <string>

#include "Texture.h"

struct SpriteFrame
{
};

class Sprite : public Texture
{
public:
    Sprite();
    virtual ~Sprite() override = default;

    virtual bool Load(const std::wstring& kFileName) override;

private:
    std::map<std::wstring, SpriteFrame> frames_;
    
};
