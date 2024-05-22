#pragma once
#include "../Engine/Actor/Component/ActorComponent.h"
#include "../Engine/Math/Vector2.h"

class b2RevoluteJointDef;
class b2Body;
class b2RevoluteJoint;
class b2World;

class HingeJointComponent : public ActorComponent
{
public:
	HingeJointComponent(class Actor* owner, const std::wstring& kName);
	virtual ~HingeJointComponent() = default;

	void ConnectedRigidBody(Actor* target);
	void SetLimits(const float& lower, const float& upper);
	void SetMaxMotorTorque(const float& value);
	void SetMotorSpeed(const float& value);


protected:
	virtual inline void InitializeComponent() override;
	virtual inline void UninitializeComponent() override;



private:
	b2RevoluteJointDef* jointDef_;
	Actor* owner_;
	b2RevoluteJoint* joint_;
	b2World* world_;
};

