#pragma once
#include "BaseJointComponent.h"
#include "../Engine/Math/Vector2.h"
#include "DistanceJoint.h"


class DistanceJointComponent : public BaseJointComponent<DistanceJoint>
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
	Actor* owner_;
	b2World* world_;
	b2DistanceJointDef* jointDef_;
};