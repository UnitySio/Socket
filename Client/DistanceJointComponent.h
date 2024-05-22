#pragma once
#include "../Engine/Actor/Component/ActorComponent.h"
#include "../Engine/Math/Vector2.h"

class b2DistanceJointDef;
class b2DistanceJoint;
class b2World;

class DistanceJointComponent : public ActorComponent
{
public:
	DistanceJointComponent(class Actor* owner, const std::wstring& kName);
	virtual ~DistanceJointComponent() = default;

	void EnableCollision(const bool& flag);
	void ConnectedRigidBody(Actor* target);
	void ConnectedAnchor(const Math::Vector2& pos);
	void Anchor(const Math::Vector2& pos);
	void AutoConfigureConnectedAnchor();
	void Distance(const float& distance);
	void MaxDistanceOnly(const bool& flag);
	void SetMaxDistance(const float& distance);
	void SetMinDistance(const float& distance);
	void SetDampingValue(const float& value);
	void SetStiffness(const float& value);

protected:
	virtual inline void InitializeComponent() override;
	virtual inline void UninitializeComponent() override;


private:
	b2DistanceJointDef* jointDef_;
	b2DistanceJoint* joint_;
	Actor* owner_;
	b2World* world_;
};