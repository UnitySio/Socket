#pragma once
#include "BaseJointComponent.h"
#include "../Engine/Math/Vector2.h"


class DistanceJointComponent : public BaseJointComponent<b2DistanceJoint, b2DistanceJointDef>
{
public:
	class DistanceJoint
	{
		DistanceJoint(DistanceJointComponent* component, b2DistanceJoint* joint) :
			component_(component),
			joint_(joint)
		{};
		
	public:
		void EnableCollision(const bool& flag);
		void ConnectedRigidBody(Actor* target);


	private:
		b2DistanceJoint* joint_;
		DistanceJointComponent* component_;
		friend class DistanceJointComponent;
	};

public:
	DistanceJointComponent(class Actor* owner, const std::wstring& kName);
	virtual ~DistanceJointComponent() = default;
	DistanceJoint* GetJoint() { return jointBody_; }

protected:
	virtual void CreateJoint() override;
	virtual inline void InitializeComponent() override;
	virtual inline void UninitializeComponent() override;
	
	virtual void SetDefaultProperties() override;

private:
	Actor* owner_;
	DistanceJoint* jointBody_;
};

