#include "MainMap.h"

#include "Actor/Pawn.h"

MainMap::MainMap(World* world, const std::wstring& kName) : Level(world, kName)
{
}

void MainMap::Load()
{
    // std::shared_ptr<Actor> pawn = std::make_shared<Pawn>(GetWorld(), L"Pawn");
    // AddActor(pawn);
}
