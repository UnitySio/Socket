#pragma once
#include "Level/Level.h"

class WorldMap : public Level
{
public:
    WorldMap(const std::wstring& kName);
    virtual ~WorldMap() override = default;

    virtual void Load() override;
    
};
