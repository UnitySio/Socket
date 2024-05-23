#include "MainMap.h"

#include "../Actor/FollowCamera.h"
#include "../Actor/Floor.h"
#include "../Actor/Pawn.h"
#include "../Engine/Actor/Component/TransformComponent.h"
#include "../Engine/Actor/Component/RigidBodyComponent.h"
#include "../DistanceJointComponent.h"
#include "../FixedJointComponent.h"
#include "../BaseJointComponent.h"

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
        pawn->GetComponent<DistanceJointComponent>()->GetJoint()->ConnectedRigidBody(pawn3);
        flag = true;
    }


    if (timer > 6.0f)
    {
        pawn->GetComponent<DistanceJointComponent>()->GetJoint()->Distance(0.2f);
        pawn->GetComponent<DistanceJointComponent>()->GetJoint()->SetMaxDistance(0.2f);
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
    pawn2->GetTransform()->SetRelativeLocation(Math::Vector2(0.0f, 7.5f));
    pawn2->GetComponent<RigidBodyComponent>()->SetBodyType(BodyType::kStatic);
    
    pawn->CreateComponent<DistanceJointComponent>(L"Fixed");
    pawn->GetComponent<DistanceJointComponent>()->CreateJointDef(pawn2);
    pawn->GetComponent<DistanceJointComponent>()->GetJoint()->Distance(0.2f);
    


    pawn->GetComponent<RigidBodyComponent>()->AddForce(Math::Vector2(5.0f, 0.0f));

    FollowCamera* camera = dynamic_cast<FollowCamera*>(follow_camera);
    camera->SetTarget(pawn);

    
}


#pragma region Joint
void MainMap::PhysicsTick(float dt)
{
    Level::PhysicsTick(dt);
    DestroyReservedJoint();
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

void MainMap::ReserveCreateJoint(b2Joint* joint, b2JointDef* jointDef, std::function<void(b2Joint*, b2JointDef*, b2World*)> func)
{
    createContainer_.push_back(std::tuple<b2Joint*, b2JointDef*, std::function<void(b2Joint*, b2JointDef*, b2World*)>>(joint, jointDef, func));
}

void MainMap::CreateReservedJoint()
{
    if (createContainer_.size() > 0)
    {
        for (auto& temp : createContainer_)
        {
            auto joint = std::get<0>(temp);
            auto jointDef = std::get<1>(temp);
            auto functor = std::get<2>(temp);
            
            
            joint = World::Get()->physics_world_->CreateJoint(jointDef);
            functor(joint, jointDef, World::Get()->physics_world_.get());
            
        }
        createContainer_.clear();
    }
}
#pragma endregion