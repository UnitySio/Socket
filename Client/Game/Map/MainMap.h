#pragma once
#include "Level/Level.h"

class MainMap : public Level
{
    SHADER_CLASS_HELPER(MainMap)
    GENERATED_BODY(MainMap, Level)
    
public:
    MainMap(const std::wstring& kName);
    virtual ~MainMap() override = default;

    virtual void Load() override;

};
