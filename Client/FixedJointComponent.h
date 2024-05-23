#pragma once
#include "BaseJointComponent.h"
#include "FixedJoint.h"

class FixedJointComponent : public BaseJointComponent<FixedJoint, b2DistanceJointDef>
{
	using Super = BaseJointComponent;
public:
	FixedJointComponent(class Actor* owner, const std::wstring& kName);
	virtual ~FixedJointComponent() = default;



protected:
	virtual inline void InitializeComponent() override;
	virtual inline void UninitializeComponent() override;


private:
	Actor* owner_;

};

