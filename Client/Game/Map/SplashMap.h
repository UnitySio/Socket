#pragma once
#include "Level/Level.h"

class SplashMap : public Level
{
    SHADER_CLASS_HELPER(SplashMap)
    GENERATED_BODY(SplashMap, Level)
    
public:
    SplashMap(const std::wstring& kName);
    virtual ~SplashMap() override = default;

    virtual void Load() override;
    
};
