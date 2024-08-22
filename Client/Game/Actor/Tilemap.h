#pragma once
#include "Actor/Actor.h"

class Tilemap : public Actor
{
    SHADER_CLASS_HELPER(Tilemap)
    
public:
    Tilemap(const std::wstring& kName);
    virtual ~Tilemap() override = default;

private:
    class TilemapComponent* tilemap_component_;
    
};
