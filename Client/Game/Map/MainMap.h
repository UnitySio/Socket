#pragma once
#include "Level/Level.h"
#include "../Engine/Input/Keyboard.h"

class TilemapComponent;

class MainMap : public Level
{
public:
    MainMap(const std::wstring& kName);
    virtual ~MainMap() override = default;

    virtual void Load() override;

    SHARED_PTR<Actor> pawn;
    SHARED_PTR<Actor> pawn2;

    TilemapComponent* map;
};
