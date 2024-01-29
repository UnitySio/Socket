#include "JointTest.h"

#include "Box.h"
#include "../../Engine/Core.h"
#include "../../Engine/Actor/Component/CircleComponent.h"
#include "box2d/b2_body.h"
#include "box2d/b2_distance_joint.h"
#include "box2d/b2_world.h"

JointTest::JointTest(b2World* world, const std::wstring& name) : Actor(world, name)
{
    GetBody()->SetTransform(b2Vec2(320.f, 200.f), 0.f);
    
    CircleComponent* circle = CreateComponent<CircleComponent>(L"CircleComponent");
    circle->SetRadius(8.f);
    circle->SetTrigger(true);
}

void JointTest::BeginPlay()
{
    Actor::BeginPlay();
    
    Box* box = new Box(GetWorld(), L"Box");
    SpawnActor(box);

    b2DistanceJointDef joint_def;
    joint_def.Initialize(GetBody(), box->GetBody(), GetBody()->GetPosition(), box->GetBody()->GetPosition());
    GetWorld()->CreateJoint(&joint_def);
}
