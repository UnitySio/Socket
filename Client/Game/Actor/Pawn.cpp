#include "Pawn.h"

#include <iostream>
#include <ostream>

#include "Dummy.h"
#include "../../Engine/Core.h"
#include "../../Engine/Actor/Component/Scenecomponent/CameraComponent.h"
#include "../../Engine/Actor/Component/BoxColliderComponent.h"
#include "../../Engine/Actor/Component/RigidBodyComponent.h"
#include "../../Engine/Graphics/Graphics.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Vector.h"
#include "box2d/b2_body.h"
#include "box2d/b2_revolute_joint.h"
#include "box2d/b2_world.h"

Pawn::Pawn(b2World* world, const std::wstring& kName) :
    Actor(world, kName)
{
    camera_view_ = CreateComponent<CameraComponent>(L"Camera");
    SetRootComponent(camera_view_);

    box_collider_ = CreateComponent<BoxColliderComponent>(L"BoxCollider");
    box_collider_->SetSize({32.f, 32.f});

    rigid_body_ = CreateComponent<RigidBodyComponent>(L"RigidBody");
    rigid_body_->SetBodyType(BodyType::kDynamic);
    
    SetActorLocation({0.f, -100.f});
}

void Pawn::BeginPlay()
{
    Actor::BeginPlay();

    Dummy* dummy = new Dummy(GetWorld(), L"Dummy");
    dummy->SetActorLocation({0.f, -300.f});
    SpawnActor(dummy);

    Dummy* dummy2 = new Dummy(GetWorld(), L"Dummy2");
    dummy2->SetActorLocation({0.f, -200.f});
    dummy2->GetRigidBody()->SetBodyType(BodyType::kDynamic);
    SpawnActor(dummy2);

    b2RevoluteJointDef joint_def;
    joint_def.Initialize(dummy->GetBody(), dummy2->GetBody(), dummy->GetBody()->GetWorldCenter());

    GetWorld()->CreateJoint(&joint_def);

    Dummy* dummy3 = new Dummy(GetWorld(), L"Dummy3");
    dummy3->SetActorLocation({0.f, -100.f});
    dummy3->GetRigidBody()->SetBodyType(BodyType::kDynamic);
    SpawnActor(dummy3);

    b2RevoluteJointDef joint_def2;
    joint_def2.Initialize(dummy2->GetBody(), dummy3->GetBody(), dummy2->GetBody()->GetWorldCenter());

    GetWorld()->CreateJoint(&joint_def2);
    
}

void Pawn::PhysicsTick(float delta_time)
{
    Actor::PhysicsTick(delta_time);
    
    InputManager* input = InputManager::Get();
    float h = input->IsKeyPressed(VK_RIGHT) - input->IsKeyPressed(VK_LEFT);

    rigid_body_->SetVelocity({h * 100.f, rigid_body_->GetVelocity().y});
}

void Pawn::Tick(float delta_time)
{
    Actor::Tick(delta_time);

    InputManager* input = InputManager::Get();

    if (input->IsKeyDown(VK_UP))
    {
        rigid_body_->AddForce(Vector::Up() * 500000.f, ForceMode::kImpulse);
    }

    if (input->IsKeyDown(VK_SPACE))
    {
        Dummy* dummy = new Dummy(GetWorld(), L"Dummy");
        dummy->GetRigidBody()->SetBodyType(BodyType::kDynamic);
        dummy->SetActorLocation({GetActorLocation().x, GetActorLocation().y});
        SpawnActor(dummy);
    }
}
