#pragma once
#include "../../Engine/Level/Level.h"

class MainMap : public Level
{
public:
    MainMap(class World* world, const std::wstring& kName);
    virtual ~MainMap() override = default;
    
};
