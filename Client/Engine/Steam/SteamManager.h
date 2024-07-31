#pragma once
#include "Singleton.h"

class SteamManager : public Singleton<SteamManager>
{
public:
    SteamManager();
    virtual ~SteamManager() override = default;
    
    int Init();

private:
    void Tick();
    void Shutdown();
    
};
