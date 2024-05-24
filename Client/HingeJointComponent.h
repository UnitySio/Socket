#pragma once
#include "BaseJointComponent.h"

class HingeJoint;

class HingeJointComponent : public BaseJointComponent<HingeJoint, b2RevoluteJointDef>
{
	using Super = BaseJointComponent;

public:
	HingeJointComponent(class Actor* owner, const std::wstring& kName);
	virtual ~HingeJointComponent() {};




protected:
	virtual inline void InitializeComponent() override;
	virtual inline void UninitializeComponent() override;
	void SetDefaultProperties() override;



private:

};

