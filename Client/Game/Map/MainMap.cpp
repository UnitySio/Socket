﻿#include "MainMap.h"

#include "Actor/Floor.h"
#include "Actor/FollowCamera.h"
#include "Actor/Pawn.h"
#include "Actor/Component/TransformComponent.h"
#include "../Engine/Actor/Component/RigidBodyComponent.h"
#include <Windows.h>
#include "tmxlite/Map.hpp"
#include "Actor/Component/TilemapComponent.h"

MainMap::MainMap(const std::wstring& kName) : Level(kName)
{
}

void MainMap::Load()
{
    SHARED_PTR<Actor> camera = MAKE_SHARED<FollowCamera>(L"FollowCamera");
    AddActor(camera);

   //SHARED_PTR<Actor> floor = MAKE_SHARED<Floor>(L"Floor");
   //AddActor(floor);

    pawn = MAKE_SHARED<Pawn>(L"Pawn");
    AddActor(pawn);

    pawn2 = MAKE_SHARED<Pawn>(L"Pawn");
    AddActor(pawn2);
    pawn2->GetComponent<RigidBodyComponent>()->SetGravityScale(0);
    map = pawn2->CreateComponent<TilemapComponent>(L"NoNamed");
    map->Load(".\\Game_Data\\Tile\\demo.tmx");
    

    // pawn->GetTransform()->SetRelativeLocation({3.5f, 2.f});
    pawn2->GetTransform()->SetRelativeLocation({-10.0f, 2.f});

    FollowCamera* follow_camera = dynamic_cast<FollowCamera*>(camera.get());
    follow_camera->SetFollow(pawn.get());

}
