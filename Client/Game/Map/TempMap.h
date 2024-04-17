#pragma once
#include "Level/Level.h"

class TempMap : public Level
{
public:
    TempMap(const std::wstring& kName);
    virtual ~TempMap() override = default;

    virtual void Load() override;
    
};
