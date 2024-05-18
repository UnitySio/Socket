#include "MainMap.h"

#include "../Actor/FollowCamera.h"
#include "../Actor/Floor.h"
#include "../Actor/Pawn.h"
#include "../Reflection.h"

MainMap::MainMap(const std::wstring& kName) : Level(kName)
{
    FollowCamera* follow_camera = new FollowCamera(GetWorld(), L"FollowCamera");
    AddActor(follow_camera);
    
    Floor* floor = new Floor(GetWorld(), L"Floor");
    AddActor(floor);

    Pawn* pawn = new Pawn(GetWorld(), L"Pawn");
    AddActor(pawn);

    Reflection ref(follow_camera);

    Reflection ref1(floor);

    Reflection ref2(pawn);

    //ref.typePointer->GetType();

    ref.typePointer->SetTarget(pawn);

    /*FollowCamera* camera = dynamic_cast<FollowCamera*>(follow_camera);
    camera->SetTarget(pawn);*/
}
