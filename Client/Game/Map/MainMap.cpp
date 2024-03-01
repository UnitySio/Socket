#include "MainMap.h"

#include "../Actor/FollowCamera.h"
#include "../Actor/Floor.h"
#include "../Actor/Pawn.h"

MainMap::MainMap(const std::wstring& kName) : Level(kName)
{
    Actor* follow_camera = new FollowCamera(GetWorld(), L"FollowCamera");
    AddActor(follow_camera);
    
    Actor* floor = new Floor(GetWorld(), L"Floor");
    AddActor(floor);

    Actor* pawn = new Pawn(GetWorld(), L"Pawn");
    AddActor(pawn);
    
    FollowCamera* camera = dynamic_cast<FollowCamera*>(follow_camera);
    camera->SetTarget(pawn);
}
