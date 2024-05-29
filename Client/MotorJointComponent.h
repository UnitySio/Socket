#pragma once
#include "BaseJointComponent.h"
class MotorJointComponent : public BaseJointComponent<b2MotorJoint, b2MotorJointDef>
{
	class MotorJoint
	{
		MotorJoint(MotorJointComponent* component, b2MotorJoint* joint, const bool& flag = false) :
			component_(component),
			joint_(joint)
		{
			if (flag)
			{
				const auto& temp = static_cast<b2MotorJoint*>(component_->world_->CreateJoint(JOINT_DEF));
				joint_ = const_cast<b2MotorJoint*>(temp);
			}
		};

	public:
		/// <summary>
		/// Set True if you want to create Joint Additive
		/// </summary>
		/// <param name="flag"></param>
		void CreateJoint(const bool& flag = false);
		void EnableCollision(const bool& flag);
		void ConnectedRigidBody(Actor* target);
		void SetAngularOffset(const float& value);
		void SetCorrectionFactor(const float& value);
		void SetLinearOffset(const Math::Vector2 pos);
		void SetMaxForce(const float& value);
		void SetMaxTorque(const float& value);

	private:
		b2MotorJoint* joint_;
		MotorJointComponent* component_;
		friend class MotorJointComponent;
	};

public:
	MotorJointComponent(class Actor* owner, const std::wstring& kName);
	virtual ~MotorJointComponent() = default;
	MotorJoint* GetJoint() { return jointBody_; }


protected:
	virtual void CreateJoint() override;
	virtual inline void InitializeComponent() override;
	virtual inline void UninitializeComponent() override;
	virtual void SetDefaultProperties(const bool& flag) override;

private:
	MotorJoint* jointBody_;
};

