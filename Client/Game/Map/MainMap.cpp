#include "MainMap.h"

#include "../Actor/Floor.h"
#include "../Actor/Pawn.h"
#include "../Actor/Dummy.h"

MainMap::MainMap(const std::wstring& kName) : Level(kName)
{
    AddActor<Floor>(L"Floor");
    AddActor<Pawn>(L"Pawn");
    AddActor<Dummy>(L"Dummy");
}
