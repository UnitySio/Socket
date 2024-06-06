#include "MainMap.h"

#include "Actor/Floor.h"
#include "Actor/FollowCamera.h"
#include "Actor/Pawn.h"
#include "Actor/Component/TransformComponent.h"
#include "../Engine/Actor/Component/RigidBodyComponent.h"
#include <Windows.h>

MainMap::MainMap(const std::wstring& kName) : Level(kName)
{
}

void MainMap::Load()
{
    SHARED_PTR<Actor> camera = MAKE_SHARED<FollowCamera>(L"FollowCamera");
    AddActor(camera);

    SHARED_PTR<Actor> floor = MAKE_SHARED<Floor>(L"Floor");
    AddActor(floor);

    pawn = MAKE_SHARED<Pawn>(L"Pawn");
    AddActor(pawn);

    pawn->GetTransform()->SetRelativeLocation({0.f, 2.f});

    FollowCamera* follow_camera = dynamic_cast<FollowCamera*>(camera.get());
    follow_camera->SetFollow(pawn.get());
    

}

