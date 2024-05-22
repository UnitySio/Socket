#include "MainMap.h"

#include "../Actor/FollowCamera.h"
#include "../Actor/Floor.h"
#include "../Actor/Pawn.h"
#include "../Engine/Actor/Component/TransformComponent.h"
#include "../Engine/Actor/Component/RigidBodyComponent.h"
#include "../DistanceJointComponent.h"
#include "../FrictionJointComponent.h"


MainMap::MainMap(const std::wstring& kName) : Level(kName),
    pawn2(nullptr),
    pawn3(nullptr),
    pawn(nullptr)
{
}

void MainMap::Tick(float dt)
{
    Level::Tick(dt);
    timer += dt;
    if (timer > 6.0f)
    {
        timer = 0.0f;
        pawn->GetComponent<FrictionJointComponent>()->ConnectedRigidBody(pawn3);
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
    pawn3->GetTransform()->SetRelativeLocation(Math::Vector2(2.5f, 3.5f));
    pawn3->GetComponent<RigidBodyComponent>()->SetBodyType(BodyType::kStatic);

    pawn2 = new Pawn(L"Pawn");
    AddActor(pawn2);
    pawn2->GetTransform()->SetRelativeLocation(Math::Vector2(0.0f, 5.5f));
    pawn2->GetComponent<RigidBodyComponent>()->SetBodyType(BodyType::kStatic);
    
    //pawn->CreateComponent<DistanceJointComponent>(L"DistanceJoint");
    //pawn->GetComponent<DistanceJointComponent>()->ConnectedRigidBody(pawn2);
    //pawn->GetComponent<DistanceJointComponent>()->SetMaxDistance(1.2f);
    //pawn->GetComponent<DistanceJointComponent>()->Distance(0.8f);
    //pawn->GetComponent<DistanceJointComponent>()->SetStiffness(0.2f);
    //pawn->GetComponent<DistanceJointComponent>()->SetDampingValue(0.4f);
   
    pawn->CreateComponent<FrictionJointComponent>(L"FrictionJoint");
    pawn->GetComponent<FrictionJointComponent>()->ConnectedRigidBody(pawn2);
    pawn->GetComponent<FrictionJointComponent>()->Anchor(pawn->GetTransform()->GetWorldLocation());
    
    


    pawn->GetComponent<RigidBodyComponent>()->AddForce(Math::Vector2(5.0f, 0.0f));

    FollowCamera* camera = dynamic_cast<FollowCamera*>(follow_camera);
    camera->SetTarget(pawn);

    
}