#include "Pawn.h"

#include "Box.h"
#include "../../Engine/Core.h"
#include "../../Engine/Actor/Component/Scenecomponent/ShapeComponent/BoxComponent.h"
#include "../../Engine/Actor/Component/Scenecomponent/SpriteComponent.h"
#include "../../Engine/Actor/Component/Scenecomponent/CameraComponent.h"
#include "../../Engine/Graphics/Graphics.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Level/Level.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_revolute_joint.h"

Pawn::Pawn(b2World* world, const std::wstring& kName) :
    Actor(world, kName)
{
    box_ = CreateComponent<BoxComponent>(L"Box");
    SetRootComponent(box_);
    
    box_->SetBoxExtent(b2Vec2(16.f, 16.f));

    GetBody()->SetType(b2_dynamicBody);
    GetBody()->GetFixtureList()->SetDensity(1.f);
    GetBody()->GetFixtureList()->SetFriction(0.3f);
    GetBody()->ResetMassData();
    
    SetActorLocation(b2Vec2(0.f, -100.f));

    camera_view_ = CreateComponent<CameraComponent>(L"Camera");
    camera_view_->SetupAttachment(GetRootComponent());
}

void Pawn::BeginPlay()
{
    Actor::BeginPlay();

    Actor* box = new Box(GetWorld(), L"Box");
    SpawnActor(box);

    b2Body* body = box->GetBody();
    // body->SetType(b2_dynamicBody);
    // body->GetFixtureList()->SetFriction(0.3f);
    // body->GetFixtureList()->SetDensity(1.f);
    // body->ResetMassData();
    
    box->SetActorLocation(b2Vec2(0.f, -300.f));

    Actor* box2 = new Box(GetWorld(), L"Box2");
    SpawnActor(box2);

    b2Body* body2 = box2->GetBody();
    body2->SetType(b2_dynamicBody);
    body2->GetFixtureList()->SetFriction(0.3f);
    body2->GetFixtureList()->SetDensity(1.f);
    body2->ResetMassData();
    
    box2->SetActorLocation(b2Vec2(0.f, -200.f));

    b2RevoluteJointDef joint_def;
    joint_def.Initialize(body, body2, body->GetWorldCenter());
    joint_def.enableLimit = true;
    joint_def.lowerAngle = -b2_pi / 6.f;
    joint_def.upperAngle = b2_pi / 6.f;

    b2RevoluteJoint* joint = dynamic_cast<b2RevoluteJoint*>(GetWorld()->CreateJoint(&joint_def));

    Actor* box3 = new Box(GetWorld(), L"Box3");
    SpawnActor(box3);

    b2Body* body3 = box3->GetBody();
    body3->SetType(b2_dynamicBody);
    body3->GetFixtureList()->SetFriction(0.3f);
    body3->GetFixtureList()->SetDensity(1.f);
    body3->ResetMassData();

    box3->SetActorLocation(b2Vec2(0.f, -100.f));

    b2RevoluteJointDef joint_def2;
    joint_def2.Initialize(body2, body3, body2->GetWorldCenter());
    joint_def2.enableLimit = true;
    joint_def2.lowerAngle = -b2_pi / 6.f;
    joint_def2.upperAngle = b2_pi / 6.f;

    b2RevoluteJoint* joint2 = dynamic_cast<b2RevoluteJoint*>(GetWorld()->CreateJoint(&joint_def2));
}

void Pawn::Tick(float delta_time)
{
    Actor::Tick(delta_time);

    InputManager* input = InputManager::Get();
    float h = input->IsKeyPressed(VK_RIGHT) - input->IsKeyPressed(VK_LEFT);

    GetBody()->SetLinearVelocity(b2Vec2(h * 100.f, GetBody()->GetLinearVelocity().y));

    if (input->IsKeyDown(VK_SPACE))
    {
        GetBody()->ApplyLinearImpulse(b2Vec2(0.f, -500000.f), GetBody()->GetWorldCenter(), true);
        // Destroy(this);
    }
}
