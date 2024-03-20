#include "Pawn.h"

#include <iostream>
#include <ostream>

#include "Dummy.h"
#include "../../Engine/Core.h"
#include "../../Engine/Actor/Component/SceneComponent/SceneComponent.h"
#include "../../Engine/Actor/Component/BoxColliderComponent.h"
#include "../../Engine/Actor/Component/RigidBodyComponent.h"
#include "../../Engine/Graphics/Graphics.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Vector.h"
#include "../../Engine/Level/Level.h"
#include "../../Engine/Level/World.h"

#include "../../Engine/Level/Listener/QueryCallback.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_mouse_joint.h"
#include "box2d/b2_revolute_joint.h"
#include "box2d/b2_world.h"

#include "../../Client/Engine/Actor/Component/SceneComponent/SpriteComponent.h"
#include "../../Client/Engine/Actor/Component/SceneComponent/AnimationComponent.h"


Pawn::Pawn(b2World* world, const std::wstring& kName) :
    Actor(world, kName),
    scene_(nullptr),
    box_collider_(nullptr),
    rigid_body_(nullptr),
    body_(nullptr),
    mouse_joint_(nullptr),
    dir_(1),
    bitmap_(nullptr),
    sprite_(nullptr),
    animation_(nullptr)
{
    scene_ = CreateComponent<SceneComponent>(L"Scene");
    SetRootComponent(scene_);
    
    box_collider_ = CreateComponent<BoxColliderComponent>(L"BoxCollider");
    box_collider_->SetSize({1.f, 1.f});

    rigid_body_ = CreateComponent<RigidBodyComponent>(L"RigidBody");
    rigid_body_->SetBodyType(BodyType::kDynamic);
    rigid_body_->SetFreezeRotation(true);
    
    SetActorLocation({0.f, 5.f});

    b2BodyDef body_def;
    body_ = GetWorld()->CreateBody(&body_def);
    sprite_ = CreateComponent<SpriteComponent>(L"SpriteComponent");
    animation_ = CreateComponent<AnimationComponent>(L"AnimationComponent");
}

void Pawn::BeginPlay()
{
    Actor::BeginPlay();

    Dummy* dummy = new Dummy(GetWorld(), L"Dummy");
    dummy->SetActorLocation({0.f, 6.f});
    SpawnActor(dummy);

    Dummy* dummy2 = new Dummy(GetWorld(), L"Dummy2");
    dummy2->SetActorLocation({0.f, 4.f});
    dummy2->GetRigidBody()->SetBodyType(BodyType::kDynamic);
    SpawnActor(dummy2);

    b2RevoluteJointDef joint_def;
    joint_def.Initialize(dummy->GetBody(), dummy2->GetBody(), dummy->GetBody()->GetWorldCenter());

    GetWorld()->CreateJoint(&joint_def);

    Dummy* dummy3 = new Dummy(GetWorld(), L"Dummy3");
    dummy3->SetActorLocation({0.f, 2.f});
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

    if (h == 0) return;
    dir_ = h;
    rigid_body_->SetVelocity({h * 2.f, rigid_body_->GetVelocity().y});
}

void Pawn::Tick(float delta_time)
{
    Actor::Tick(delta_time);

    InputManager* input = InputManager::Get();

    if (input->IsKeyDown(VK_UP))
    {
        rigid_body_->SetVelocity(Vector::Zero());
        rigid_body_->AddForce(Vector::Up() * 5.f, ForceMode::kImpulse);
    }

    if (input->IsKeyDown(VK_SPACE))
    {
        Dummy* dummy = new Dummy(GetWorld(), L"Dummy");
        dummy->GetRigidBody()->SetBodyType(BodyType::kDynamic);
        dummy->SetActorLocation({GetActorLocation().x, GetActorLocation().y});
        SpawnActor(dummy);
    }

    Level* level = World::Get()->GetLevel();
    b2Vec2 mouse_position = level->GetWorldPosition(input->GetMousePosition());

    if (input->IsKeyDown(MK_LBUTTON))
    {
        b2AABB aabb;
        aabb.lowerBound = mouse_position - b2Vec2(0.001f, 0.001f);
        aabb.upperBound = mouse_position + b2Vec2(0.001f, 0.001f);

        QueryCallback callback(mouse_position);
        GetWorld()->QueryAABB(&callback, aabb);

        if (callback.GetFixture())
        {
            b2Body* body = callback.GetFixture()->GetBody();

            b2MouseJointDef def;
            def.bodyA = body_;
            def.bodyB = body;
            def.target = mouse_position;
            def.maxForce = 10000.f * body->GetMass();
            b2LinearStiffness(def.stiffness, def.damping, 5.f, .7f, def.bodyA, def.bodyB);
            
            mouse_joint_ = dynamic_cast<b2MouseJoint*>(GetWorld()->CreateJoint(&def));
            body->SetAwake(true);
        }
    }

    if (input->IsKeyUp(MK_LBUTTON) && mouse_joint_)
    {
        GetWorld()->DestroyJoint(mouse_joint_);
        mouse_joint_ = nullptr;
    }

    if (input->IsKeyPressed(MK_LBUTTON) && mouse_joint_)
    {
        mouse_joint_->SetTarget(mouse_position);
    }
}

void Pawn::Render()
{
    Actor::Render();
}
