#include "Dummy.h"

#include "../../Engine/Actor/Component/BoxColliderComponent.h"
#include "../../Engine/Actor/Component/RigidBodyComponent.h"
#include "../../Engine/Actor/Component/SceneComponent/SceneComponent.h"
#include "box2d/b2_math.h"

Dummy::Dummy(b2World* world, const std::wstring& kName) :
    Actor(world, kName)
{
    SceneComponent* root = CreateComponent<SceneComponent>(L"Root");
    SetRootComponent(root);
    
    box_collider_ = CreateComponent<BoxColliderComponent>(L"BoxCollider");
    box_collider_->SetSize({1.f, 1.f});

    rigid_body_ = CreateComponent<RigidBodyComponent>(L"RigidBody");
    rigid_body_->SetBodyType(BodyType::kStatic);
}
