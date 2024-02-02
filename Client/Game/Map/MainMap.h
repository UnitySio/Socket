#pragma once
#include "../../Engine/Scene/Level.h"

class MainMap : public Level
{
public:
    MainMap(const std::wstring& kName);
    virtual ~MainMap() override = default;
    
};
