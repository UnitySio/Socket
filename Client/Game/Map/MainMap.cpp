﻿#include "pch.h"
#include "MainMap.h"

#include "Actor/Capsule.h"
#include "Actor/FollowCamera.h"
#include "Actor/Tilemap.h"
#include "Actor/Character/Player/PlayerController.h"
#include "Actor/Test/Platform.h"

MainMap::MainMap(const std::wstring& kName) : Level(kName)
{
}

void MainMap::Load()
{
    FollowCamera* camera = AddActor<FollowCamera>(L"FollowCamera");
    Tilemap* tilemap = AddActor<Tilemap>(L"Tilemap");
    
    PlayerController* player = AddActor<PlayerController>(L"Player");
    camera->SetFollow(player);

    Platform* platform = AddActor<Platform>(L"Platform");
    Capsule* capsule = AddActor<Capsule>(L"capsule");
}
