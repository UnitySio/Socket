#include "pch.h"
#include "MainMap.h"

#include "Actor/FollowCamera.h"
#include "Actor/Tilemap.h"
#include "Actor/Character/Player/PlayerController.h"
#include "Actor/Component/TransformComponent.h"
#include "Level/World.h"

MainMap::MainMap(const std::wstring& kName) : Level(kName)
{
}

void MainMap::Load()
{
    Tilemap* tilemap = AddActor<Tilemap>(L"Tilemap");
    PlayerController* player = AddActor<PlayerController>(L"Player");
    FollowCamera* camera = AddActor<FollowCamera>(L"FollowCamera");
    camera->SetFollow(player);
}
