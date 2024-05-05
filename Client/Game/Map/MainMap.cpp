#include "MainMap.h"

#include "Actor/Pawn.h"

MainMap::MainMap(World* world, const std::wstring& kName) : Level(world, kName)
{
}

void MainMap::Load()
{
    Actor* pawn = new Pawn(GetWorld(), L"Pawn");
    AddActor(pawn);
}
