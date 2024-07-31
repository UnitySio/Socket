#include "pch.h"
#include "SteamManager.h"

#include "steam/steam_api.h"

SteamManager::SteamManager()
{
}

int SteamManager::Init()
{
    if (SteamAPI_RestartAppIfNecessary(ProjectSettings::kSteamAppID))
    {
        return 1;
    }

    if (!SteamAPI_Init())
    {
        return -1;
    }

    return 0;
}

void SteamManager::Tick()
{
    SteamAPI_RunCallbacks();
}

void SteamManager::Shutdown()
{
    SteamAPI_Shutdown();
}
