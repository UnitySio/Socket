#include "MainMap.h"

#include "../Actor/Floor.h"
#include "../Actor/Pawn.h"

MainMap::MainMap(const std::wstring& kName) : Scene(kName)
{
    Actor* floor = new Floor(GetWorld(), L"Floor");
    AddActor(floor);
    
    Actor* pawn = new Pawn(GetWorld(), L"Pawn");
    AddActor(pawn);
}
