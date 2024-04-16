#include "MainMap.h"

#include "../Actor/FollowCamera.h"
#include "../Actor/Floor.h"
#include "../Actor/Pawn.h"
#include "Actor/Dummy.h"

MainMap::MainMap(const std::wstring& kName) : Level(kName)
{
    Actor* follow_camera = new FollowCamera(L"FollowCamera");
    AddActor(follow_camera);
    
    Actor* floor = new Floor(L"Floor");
    AddActor(floor);

    Actor* pawn = new Pawn(L"Pawn");
    AddActor(pawn);

    Actor* dummy = new Dummy(L"Dummy");
    AddActor(dummy);
    
    FollowCamera* camera = dynamic_cast<FollowCamera*>(follow_camera);
    camera->SetTarget(pawn);
}
