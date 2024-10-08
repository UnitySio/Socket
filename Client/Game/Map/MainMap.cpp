﻿#include "pch.h"
#include "MainMap.h"

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
    Platform* platform = AddActor<Platform>(L"Platform");
}

RTTR_REGISTRATION
{
    rttr::registration::class_<MainMap>("MainMap")
        .constructor<const std::wstring&>()
        (
            rttr::policy::ctor::as_std_shared_ptr
        );
}
