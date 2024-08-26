#pragma once
#include "Singleton.h"

class SteamManager : public Singleton<SteamManager>
{
public:
    SteamManager();
    virtual ~SteamManager() override = default;
    
    int Init();
    void Shutdown();

private:
    friend class GameEngine;
    
    void Tick();
    
};
