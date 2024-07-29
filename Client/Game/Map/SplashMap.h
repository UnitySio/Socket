#pragma once
#include "Level/Level.h"

class SplashMap : public Level
{
public:
    SplashMap(const std::wstring& kName);
    virtual ~SplashMap() override = default;

    virtual void Load() override;
    
};
