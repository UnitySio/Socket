#pragma once
#include "BaseJointComponent.h"

class WheelJointComponent : public BaseJointComponent<b2WheelJoint, b2WheelJointDef>
{
	class WheelJoint
	{
		WheelJoint(WheelJointComponent* component, b2WheelJoint* joint, const bool& flag = false) :
			component_(component),
			joint_(joint)
		{
			if (flag)
			{
				const auto& temp = static_cast<b2WheelJoint*>(component_->world_->CreateJoint(JOINT_DEF));
				joint_ = const_cast<b2WheelJoint*>(temp);
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
		void Anchor(const Math::Vector2& pos);
		void ConnectedAnchor(const Math::Vector2& pos);
		void SetDamping(const float& value);
		void SetLimits(const float& lower, const float& upper);
		void SetMaxMortorTorque(const float& value);
		void SetMotorSpeed(const float& value);
		void SetStiffness(const float& value);
		

	private:
		b2WheelJoint* joint_;
		WheelJointComponent* component_;
		friend class WheelJointComponent;
	};

public:
	WheelJointComponent(class Actor* owner, const std::wstring& kName);
	virtual ~WheelJointComponent() = default;
	WheelJoint* GetJoint() { return jointBody_; }


protected:
	virtual void CreateJoint() override;
	virtual inline void InitializeComponent() override;
	virtual inline void UninitializeComponent() override;
	virtual void SetDefaultProperties(const bool& flag) override;

private:
	WheelJoint* jointBody_;
};

