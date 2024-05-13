#pragma once
#include "Texture.h"

class Sprite : Texture
{
public:
    Sprite();
    virtual ~Sprite() override = default;

    virtual bool Load(const std::wstring& kFileName) override;
    
};
