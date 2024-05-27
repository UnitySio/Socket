#pragma once
#include "BaseJointComponent.h"
class HingeJointComponent : public BaseJointComponent<b2RevoluteJoint, b2RevoluteJointDef>
{
	class HingeJoint
	{
		HingeJoint(HingeJointComponent* component, b2RevoluteJoint* joint, const bool& flag = false) :
			component_(component),
			joint_(joint)
		{
			if (flag)
			{
				const auto& temp = static_cast<b2RevoluteJoint*>(component_->world_->CreateJoint(JOINT_DEF));
				joint_ = const_cast<b2RevoluteJoint*>(temp);

			}
				
		};

	public:
		void CreateJoint(const bool& flag = false);
		void EnableCollision(const bool& flag);
		void ConnectedRigidBody(Actor* target);
		void Anchor(const Math::Vector2& pos);
		void ConnectedAnchor(const Math::Vector2& pos);
		void SetUseMotor(const bool& flag);
		void SetMotorSpeed(const float& value);
		void SetMaxTorque(const float& value);
		void SetLimitsEnabled(const bool& flag);
		void SetLimitLowerUpper(const float& lower, const float& upper);


	private:
		
		b2RevoluteJoint* joint_;
		HingeJointComponent* component_;
		friend class HingeJointComponent;
	};
public:
	HingeJointComponent(class Actor* owner, const std::wstring& kName);
	virtual ~HingeJointComponent() {}
	HingeJoint* GetJoint() { return jointBody_; }

protected:
	virtual inline void InitializeComponent() override;
	virtual inline void UninitializeComponent() override;

private:
	void CreateJoint() override;
	void SetDefaultProperties(const bool& flag) override;


	HingeJoint* jointBody_;
};

