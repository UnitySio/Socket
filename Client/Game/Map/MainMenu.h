#pragma once
#include "Level/Level.h"

class MainMenu : public Level
{
public:
    MainMenu(const std::wstring& kName);
    virtual ~MainMenu() override = default;

    virtual void Load() override;
    
};
