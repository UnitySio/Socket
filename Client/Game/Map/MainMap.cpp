#include "pch.h"
#include "MainMap.h"

#include "Actor/Capsule.h"
#include "Actor/Tilemap.h"
#include "Actor/Character/Player/PlayerController.h"
#include "Actor/Test/Platform.h"
#include "Actor/Dummy/Dummy.h"

MainMap::MainMap(const std::wstring& kName) : Level(kName)
{
}

void MainMap::Load()
{
    Tilemap* tilemap = AddActor<Tilemap>(L"Tilemap");
    // PlayerController* player = AddActor<PlayerController>(L"Player");
    // Platform* platform = AddActor<Platform>(L"Platform");
    Capsule* capsule = AddActor<Capsule>(L"capsule");

    Dummy* dummy = AddActor<Dummy>(L"Dummy");
}
