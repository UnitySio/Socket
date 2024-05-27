#pragma once
#include "BaseJointComponent.h"
#include "../Engine/Math/Vector2.h"

class DistanceJointComponent : public BaseJointComponent<b2DistanceJoint, b2DistanceJointDef>
{
	class DistanceJoint
	{
		DistanceJoint(DistanceJointComponent* component, b2DistanceJoint* joint, const bool& flag = false) :
			component_(component),
			joint_(joint)
		{
			if (flag)
			{
				const auto& temp = static_cast<b2DistanceJoint*>(component_->world_->CreateJoint(JOINT_DEF));
				joint_ = const_cast<b2DistanceJoint*>(temp);
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
		void Distance(const float& value);
		void SetMaxDistance(const float& value);
		void SetMinDistance(const float& value);
		void SetDampingRatio(const float& value);
		void SetStiffness(const float& value);

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
	virtual void SetDefaultProperties(const bool& flag) override;

private:
	DistanceJoint* jointBody_;
};