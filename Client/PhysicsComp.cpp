#include "PhysicsComp.h"
#include "Sio.h"
#include "box2d/b2_body.h"
#include "Engine/Actor/Component/RigidBodyComponent.h"
#include "Engine/Actor/Component/BoxColliderComponent.h"

PhysicsComp::PhysicsComp(Actor* owner, const std::wstring& kName)
	:ActorComponent(owner, kName)
{
	owner_ = owner;
	name_ = kName;
}

void PhysicsComp::BeginPlay()
{
	Super::BeginPlay();
	box_collider_ = std::make_shared<BoxColliderComponent>(owner_, name_);
	rigid_body_ = std::make_shared<RigidBodyComponent>(owner_, name_);

	
	box_collider_->SetSize({ 1.f, 1.f });

	rigid_body_->SetBodyType(BodyType::kDynamic);
	rigid_body_->SetFreezeRotation(true);
}
