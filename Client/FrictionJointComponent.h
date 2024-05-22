#pragma once
#include "../Engine/Actor/Component/ActorComponent.h"
#include "../Engine/Math/Vector2.h"

class b2FrictionJointDef;
class b2World;
class Actor;
class b2FrictionJoint;

class FrictionJointComponent : public ActorComponent
{
public:
	FrictionJointComponent(class Actor* owner, const std::wstring& kName);
	virtual ~FrictionJointComponent() = default;

	void EnableCollision(const bool& flag);
	void ConnectedRigidBody(Actor* target);
	void Anchor(const Math::Vector2& pos);
	void ConnectedAnchor(const Math::Vector2& pos);
	void MaxForce(const float& value);
	void MaxTorque(const float& value);


protected:
	virtual inline void InitializeComponent() override;
	virtual inline void UninitializeComponent() override;

private:
	b2FrictionJointDef* jointDef_;
	b2FrictionJoint* joint_;
	Actor* owner_;
	b2World* world_;
};

