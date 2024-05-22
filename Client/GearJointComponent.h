#pragma once
#include "../Engine/Actor/Component/ActorComponent.h"
#include "../Engine/Math/Vector2.h"

class b2GearJointDef;
class b2Body;
class b2GearJoint;
class b2World;


class GearJointComponent : public ActorComponent
{
public:
	GearJointComponent(class Actor* owner, const std::wstring& kName);
	virtual ~GearJointComponent() = default;

	void EnableCollision(const bool& flag);
	void ConnectedRigidBody(Actor* target);
	void SetRatio(const float& value);

protected:
	virtual inline void InitializeComponent() override;
	virtual inline void UninitializeComponent() override;



private:
	b2GearJointDef* jointDef_;
	b2GearJoint* joint_;
	Actor* owner_;
	b2World* world_;



};

