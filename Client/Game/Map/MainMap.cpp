#include "MainMap.h"

#include "../Actor/FollowCamera.h"
#include "../Actor/Floor.h"
#include "../Actor/Pawn.h"
#include "../Engine/Actor/Component/TransformComponent.h"
#include "../Engine/Actor/Component/RigidBodyComponent.h"
#include "../DistanceJointComponent.h"


MainMap::MainMap(const std::wstring& kName) : Level(kName),
    pawn2(nullptr),
    pawn3(nullptr),
    pawn(nullptr),
    flag(false)
{
}

void MainMap::Tick(float dt)
{
    Level::Tick(dt);
    timer += dt;


    if (timer > 3.0f && !flag)
    {
        flag = true;
    }


    if (timer > 6.0f)
    {
        pawn->GetComponent<DistanceJointComponent>()->GetJoint()->ConnectedRigidBody(pawn3);
        timer = 0.0f;
    }
}

void MainMap::Load()
{
    Actor* follow_camera = new FollowCamera(L"FollowCamera");
    AddActor(follow_camera);
    
    Actor* floor = new Floor(L"Floor");
    AddActor(floor);

    pawn = new Pawn(L"Pawn");
    AddActor(pawn);
    pawn->GetTransform()->SetRelativeLocation(Math::Vector2(0.0f, 3.5f));

    pawn3 = new Pawn(L"Pawn");
    AddActor(pawn3);
    pawn3->GetTransform()->SetRelativeLocation(Math::Vector2(5.5f, 3.5f));
    pawn3->GetComponent<RigidBodyComponent>()->SetBodyType(BodyType::kStatic);

    pawn2 = new Pawn(L"Pawn");
    AddActor(pawn2);
    pawn2->GetTransform()->SetRelativeLocation(Math::Vector2(0.0f, 5.5f));
    pawn2->GetComponent<RigidBodyComponent>()->SetBodyType(BodyType::kStatic);
    
    pawn->CreateComponent<DistanceJointComponent>(L"DistanceJoint");
    pawn->GetComponent<DistanceJointComponent>()->CreateJointDef(pawn2);
    pawn->GetComponent<DistanceJointComponent>()->GetJoint()->Distance(0.8f);
    pawn->GetComponent<DistanceJointComponent>()->GetJoint()->SetMaxDistance(0.8f);
    
    

    
    
    


    pawn->GetComponent<RigidBodyComponent>()->AddForce(Math::Vector2(5.0f, 0.0f));

    FollowCamera* camera = dynamic_cast<FollowCamera*>(follow_camera);
    camera->SetTarget(pawn);

    
}