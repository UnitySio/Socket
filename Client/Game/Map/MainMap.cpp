#include "MainMap.h"

#include "Actor/Floor.h"
#include "Actor/FollowCamera.h"
#include "Actor/Pawn.h"
#include "Actor/Component/TransformComponent.h"

MainMap::MainMap(World* world, const std::wstring& kName) : Level(world, kName)
{
}

void MainMap::Load()
{
    std::shared_ptr<Actor> camera = std::make_shared<FollowCamera>(GetWorld(), L"FollowCamera");
    AddActor(camera);

    std::shared_ptr<Actor> floor = std::make_shared<Floor>(GetWorld(), L"Floor");
    AddActor(floor);

    std::shared_ptr<Actor> pawn = std::make_shared<Pawn>(GetWorld(), L"Pawn");
    AddActor(pawn);

    pawn->GetTransform()->SetRelativeLocation({0.f, 2.f});

    FollowCamera* follow_camera = dynamic_cast<FollowCamera*>(camera.get());
    follow_camera->SetFollow(pawn.get());
}
