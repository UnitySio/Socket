#include "MainMap.h"

#include "../Actor/FollowCamera.h"
#include "../Actor/Floor.h"
#include "../Actor/Pawn.h"
#include "Actor/Dummy.h"

MainMap::MainMap(World* world, const std::wstring& kName) : Level(world, kName)
{
    Actor* follow_camera = new FollowCamera(GetPhysicsWorld(), L"FollowCamera");
    AddActor(follow_camera);
    
    Actor* floor = new Floor(GetPhysicsWorld(), L"Floor");
    AddActor(floor);

    Actor* pawn = new Pawn(GetPhysicsWorld(), L"Pawn");
    AddActor(pawn);

    Actor* dummy = new Dummy(GetPhysicsWorld(), L"Dummy");
    AddActor(dummy);
    
    FollowCamera* camera = dynamic_cast<FollowCamera*>(follow_camera);
    camera->SetTarget(pawn);
}
