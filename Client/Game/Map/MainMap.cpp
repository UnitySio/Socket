#include "MainMap.h"

#include "Actor/FollowCamera.h"
#include "../Engine/Actor/Component/RigidBodyComponent.h"
#include <Windows.h>

#include "Actor/Tilemap.h"
#include "Actor/Character/Player/PlayerController.h"
#include "tmxlite/Map.hpp"
#include "Actor/Component/Tilemap/TilemapComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Misc/Delegate.h"
#include "Misc/Function.h"
#include "UI/Canvas.h"
#include "UI/Button.h"
#include "UI/ProgressBar.h"
#include "UI/ScrollView.h"
#include "UI/TextBlock.h"

MainMap::MainMap(const std::wstring& kName) : Level(kName)
{
}

void MainMap::Load()
{
    SHARED_PTR<Actor> tilemap = MAKE_SHARED<Tilemap>(L"Tilemap");
    AddActor(tilemap);

    SHARED_PTR<Actor> player = MAKE_SHARED<PlayerController>(L"Player");
    AddActor(player);
    player->GetTransform()->SetRelativePosition({ 1.5f, 0.f });

    // SHARED_PTR<Actor> player2 = MAKE_SHARED<PlayerController>(L"Player");
    // AddActor(player2);
    // player2->GetComponent<RigidBodyComponent>()->SetGravityScale(0.0f);
    // player2->GetComponent<RigidBodyComponent>()->SetBodyType(BodyType::kStatic);
    //
    // auto joint = player->CreateComponent<DistanceJointComponent>(L"Joint");
    // joint->CreateJointDefWithTarget(player2);
    // joint->GetJoint()->Distance(2.0f);

    
    SHARED_PTR<Actor> camera = MAKE_SHARED<FollowCamera>(L"FollowCamera");
    AddActor(camera);
    
    FollowCamera* follow_camera = dynamic_cast<FollowCamera*>(camera.get());
    follow_camera->SetFollow(player.get());
    
}

#pragma region Joint
void MainMap::PhysicsTick(float dt)
{
    Level::PhysicsTick(dt);

    if (destroyContainer_.size() > 0)
        DestroyReservedJoint();

    if (createContainer_.size() > 0)
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

void MainMap::ReserveCreateJoint(std::function<void()>&& func)
{
    createContainer_.push_back(std::move(func));
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