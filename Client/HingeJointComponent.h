#pragma once
#include "BaseJointComponent.h"
class HingeJointComponent : public BaseJointComponent<b2RevoluteJoint, b2RevoluteJointDef>
{
	class HingeJoint
	{
		HingeJoint(HingeJointComponent* component, b2RevoluteJoint* joint) :
			component_(component),
			joint_(joint)
		{};

	public:
		void EnableCollision(const bool& flag);
		void ConnectedRigidBody(Actor* target);
		void Anchor(const Math::Vector2& pos);
		void ConnectedAnchor(const Math::Vector2& pos);


	private:
		b2RevoluteJoint* joint_;
		HingeJointComponent* component_;
		friend class HingeJointComponent;
	};
public:
	HingeJointComponent(class Actor* owner, const std::wstring& kName);
	virtual ~HingeJointComponent() {}

protected:
	virtual inline void InitializeComponent() override;
	virtual inline void UninitializeComponent() override;

private:
	void CreateJoint() override;
	void SetDefaultProperties(const bool& flag) override;



};

