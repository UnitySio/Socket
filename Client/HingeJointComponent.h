#pragma once
#include "BaseJointComponent.h"
#include "HingeJoint.h"

class HingeJoint;

class HingeJointComponent : public BaseJointComponent<HingeJoint, b2RevoluteJointDef>
{
public:
	HingeJointComponent(class Actor* owner, const std::wstring& kName);
	virtual ~HingeJointComponent() {};
	virtual void CreateJoint() override;
	using Super::CreateJoint;



protected:
	virtual inline void InitializeComponent() override;
	virtual inline void UninitializeComponent() override;
	virtual void SetDefaultProperties() override;



private:
	friend class HingeJoint;

};

