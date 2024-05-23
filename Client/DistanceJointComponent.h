#pragma once
#include "BaseJointComponent.h"
#include "../Engine/Math/Vector2.h"
#include "DistanceJoint.h"


class DistanceJointComponent : public BaseJointComponent<DistanceJoint, b2DistanceJointDef>
{
public:
	DistanceJointComponent(class Actor* owner, const std::wstring& kName);
	virtual ~DistanceJointComponent() = default;

	

protected:
	virtual inline void InitializeComponent() override;
	virtual inline void UninitializeComponent() override;


private:
	Actor* owner_;
	b2World* world_;

};