#include "Dummy.h"

#include "../../Engine/Actor/Component/BoxColliderComponent.h"
#include "../../Engine/Actor/Component/SceneComponent/SceneComponent.h"
#include "box2d/b2_math.h"

Dummy::Dummy(b2World* world, const std::wstring& kName) :
    Actor(world, kName)
{
    SceneComponent* root = CreateComponent<SceneComponent>(L"Root");
    SetRootComponent(root);
    
    box_collider_ = CreateComponent<BoxColliderComponent>(L"BoxCollider");
    box_collider_->SetSize({64.f, 64.f});
    box_collider_->SetTrigger(true);

    SetActorLocation({0.f, -32.f});
}
