#include "MainMap.h"

#include "Actor/FollowCamera.h"
#include "../Engine/Actor/Component/RigidBodyComponent.h"
#include <Windows.h>

#include "Actor/Tilemap.h"
#include "Actor/Character/Player/PlayerController.h"
#include "tmxlite/Map.hpp"
#include "Actor/Component/Tilemap/TilemapComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Misc/Delegate.h"
#include "Misc/Function.h"
#include "UI/Canvas.h"
#include "UI/Button.h"
#include "UI/ProgressBar.h"
#include "UI/ScrollView.h"
#include "UI/TextBlock.h"

MainMap::MainMap(const std::wstring& kName) : Level(kName)
{
}

void MainMap::Load()
{
    SHARED_PTR<Actor> tilemap = MAKE_SHARED<Tilemap>(L"Tilemap");
    AddActor(tilemap);

    SHARED_PTR<Actor> player = MAKE_SHARED<PlayerController>(L"Player");
    AddActor(player);
    
    player->GetTransform()->SetRelativePosition({.5f, 2.f});
    
    SHARED_PTR<Actor> camera = MAKE_SHARED<FollowCamera>(L"FollowCamera");
    AddActor(camera);
    
    FollowCamera* follow_camera = dynamic_cast<FollowCamera*>(camera.get());
    follow_camera->SetFollow(player.get());
    
}