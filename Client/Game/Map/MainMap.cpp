#include "MainMap.h"

#include "Actor/Floor.h"
#include "Actor/FollowCamera.h"

MainMap::MainMap(World* world, const std::wstring& kName) : Level(world, kName)
{
}

void MainMap::Load()
{
    std::shared_ptr<FollowCamera> camera = std::make_shared<FollowCamera>(GetWorld(), L"FollowCamera");
    AddActor(camera);

    std::shared_ptr<Floor> floor = std::make_shared<Floor>(GetWorld(), L"Floor");
    AddActor(floor);
}
