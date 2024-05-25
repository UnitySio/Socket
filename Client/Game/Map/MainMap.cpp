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
    flag1(false),
    flag2(false)
{
}

void MainMap::Tick(float dt)
{
    Level::Tick(dt);
    timer += dt;


    if (timer > 3.0f && !flag1)
    {
        pawn->GetComponent<DistanceJointComponent>()->GetJoint()->ConnectedRigidBody(pawn3);
        flag1 = true;
    }


    if (timer > 6.0f && !flag2)
    {
        pawn->GetComponent<DistanceJointComponent>()->ConnectedRigidBody(pawn2);

        timer = 0.0f;
        flag2 = true;
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
    pawn2->GetTransform()->SetRelativeLocation(Math::Vector2(0.0f, 7.5f));
    pawn2->GetComponent<RigidBodyComponent>()->SetBodyType(BodyType::kStatic);
    
    pawn->CreateComponent<DistanceJointComponent>(L"Fixed");
    pawn->GetComponent<DistanceJointComponent>()->CreateJointDefWithTarget(pawn2);
    pawn->GetComponent<DistanceJointComponent>()->CreateJoint();
    
    


    pawn->GetComponent<RigidBodyComponent>()->AddForce(Math::Vector2(10.0f, 0.0f));

    FollowCamera* camera = dynamic_cast<FollowCamera*>(follow_camera);
    camera->SetTarget(pawn);

    
}


#pragma region Joint
void MainMap::PhysicsTick(float dt)
{
    Level::PhysicsTick(dt);
    
    if(destroyContainer_.size() > 0)
        DestroyReservedJoint();

    if(createContainer_.size() > 0)
        CreateReservedJoint();
}

void MainMap::ReserveDestroyJoint(b2Joint* joint)
{
    destroyContainer_.push_back(joint);
}


void MainMap::DestroyReservedJoint()
{
    if (destroyContainer_.size() > 0)
    {
        for (auto& temp : destroyContainer_)
        {
            World::Get()->physics_world_->DestroyJoint(temp);
        }
        destroyContainer_.clear();
    }
}

void MainMap::ReserveCreateJoint(std::function<void()> func)
{
    createContainer_.push_back(func);
}

void MainMap::CreateReservedJoint()
{
    if (createContainer_.size() > 0)
    {
        for (auto& temp : createContainer_)
        {
            temp();
        }
        createContainer_.clear();
    }
}
#pragma endregion