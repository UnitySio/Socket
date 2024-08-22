#pragma once
#include "Actor/Actor.h"

class Tilemap : public Actor
{
    DECLARE_SHARED_CLASS(Tilemap, Actor)
    
public:
    Tilemap(const std::wstring& kName);
    virtual ~Tilemap() override = default;

private:
    class TilemapComponent* tilemap_component_;
    
};
