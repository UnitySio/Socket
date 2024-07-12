#pragma once
#include "Actor/Component/ActorComponent.h"
#include <memory>

class Actor;
class b2Body;
class BoxColliderComponent;
class RigidBodyComponent;

class PhysicsComp : public ActorComponent
{
public:
	PhysicsComp(Actor* owner, const std::wstring& kName);


protected:
	using Super = ActorComponent;
	virtual void BeginPlay() override;

private:
	b2Body* body_;

	std::shared_ptr<BoxColliderComponent> box_collider_;
	std::shared_ptr<RigidBodyComponent> rigid_body_;
};