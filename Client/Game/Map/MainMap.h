#pragma once
#include "Level/Level.h"

class MainMap : public Level
{
public:
    MainMap(World* world, const std::wstring& kName);
    virtual ~MainMap() override = default;

    virtual void Load() override;
    
};
