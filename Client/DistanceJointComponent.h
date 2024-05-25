#pragma once
#include "BaseJointComponent.h"
#include "../Engine/Math/Vector2.h"


class DistanceJointComponent : public BaseJointComponent<b2DistanceJoint, b2DistanceJointDef>
{
public:
	class DistanceJoint
	{
	public:
		DistanceJoint(DistanceJointComponent* component, b2DistanceJoint* joint) :
			component_(component),
			joint_(joint)
		{};
		

		void ConnectedRigidBody(Actor* target);

	private:
		b2DistanceJoint* joint_;
		DistanceJointComponent* component_;
		friend class DistanceJointComponent;
	};
public:
	DistanceJointComponent(class Actor* owner, const std::wstring& kName);
	virtual ~DistanceJointComponent() = default;
	void ConnectedRigidBody(Actor* target);
	DistanceJoint* GetJoint() { return jointBody_; }
	virtual void CreateJoint() override;

protected:
	virtual inline void InitializeComponent() override;
	virtual inline void UninitializeComponent() override;
	
	virtual void SetDefaultProperties() override;

private:
	Actor* owner_;
	DistanceJoint* jointBody_;
};

