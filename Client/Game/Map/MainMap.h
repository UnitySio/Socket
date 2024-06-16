#pragma once
#include "Level/Level.h"

class TilemapComponent;

class MainMap : public Level
{
public:
    MainMap(const std::wstring& kName);
    virtual ~MainMap() override = default;

    virtual void Load() override;
    
};

