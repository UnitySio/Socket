#include "pch.h"
#include "MainMap.h"

#include "Actor/Capsule.h"
#include "Actor/Tilemap.h"
#include "Actor/Character/Player/Player.h"
#include "Actor/Platform/Platform.h"

MainMap::MainMap(const std::wstring& kName) : Level(kName)
{
}

void MainMap::Load()
{
    Tilemap* tilemap = AddActor<Tilemap>(L"Tilemap");
    Player* player = AddActor<Player>(L"Player");
    Capsule* capsule = AddActor<Capsule>(L"Capsule");
    Platform* platform = AddActor<Platform>(L"Platform");
}
