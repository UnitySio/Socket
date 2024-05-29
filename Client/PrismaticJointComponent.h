#pragma once
#include "BaseJointComponent.h"
class PrismaticJointComponent : public BaseJointComponent<b2PrismaticJoint, b2PrismaticJointDef>
{
	class PrismaticJoint
	{
		PrismaticJoint(PrismaticJointComponent* component, b2PrismaticJoint* joint, const bool& flag = false) :
			component_(component),
			joint_(joint)
		{
			if (flag)
			{
				const auto& temp = static_cast<b2PrismaticJoint*>(component_->world_->CreateJoint(JOINT_DEF));
				joint_ = const_cast<b2PrismaticJoint*>(temp);
			}
		};
	public:
		void CreateJoint(const bool& flag = false);
		void EnableCollision(const bool& flag);
		void ConnectedRigidBody(Actor* target);
		void Anchor(const Math::Vector2& pos);
		void ConnectedAnchor(const Math::Vector2& pos);
		void SetMotorSpeed(const float& value);
		void SetLimits(const float& lower, const float& upper);
		void SetMaxMotorForce(const float& value);


	private:
		b2PrismaticJoint* joint_;
		PrismaticJointComponent* component_;
		friend class PrismaticJointComponent;
	};

public:
	PrismaticJointComponent(class Actor* owner, const std::wstring& kName);
	virtual ~PrismaticJointComponent() = default;
	PrismaticJoint* GetJoint() { return jointBody_; }


protected:
	virtual void CreateJoint() override;
	virtual inline void InitializeComponent() override;
	virtual inline void UninitializeComponent() override;
	virtual void SetDefaultProperties(const bool& flag) override;

private:
	PrismaticJoint* jointBody_;

};

