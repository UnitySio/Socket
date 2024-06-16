#include "MainMap.h"

#include "Actor/FollowCamera.h"
#include "Actor/Pawn.h"
#include "../Engine/Actor/Component/RigidBodyComponent.h"
#include <Windows.h>

#include "Actor/Tilemap.h"
#include "tmxlite/Map.hpp"
#include "Actor/Component/TilemapComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Misc/Delegate.h"
#include "Misc/Function.h"

MainMap::MainMap(const std::wstring& kName) : Level(kName)
{
}

void MainMap::Load()
{
    SHARED_PTR<Actor> camera = MAKE_SHARED<FollowCamera>(L"FollowCamera");
    AddActor(camera);

    SHARED_PTR<Actor> tilemap = MAKE_SHARED<Tilemap>(L"Tilemap");
    AddActor(tilemap);

    SHARED_PTR<Actor> pawn = MAKE_SHARED<Pawn>(L"Pawn");
    AddActor(pawn);

    pawn->GetTransform()->SetRelativeLocation({0.5f, 2.f});

    FollowCamera* follow_camera = dynamic_cast<FollowCamera*>(camera.get());
    follow_camera->SetFollow(pawn.get());
    
    
}
