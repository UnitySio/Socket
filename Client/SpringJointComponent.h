#pragma once
#include "BaseJointComponent.h"
#include "SpringJoint.h"
class SpringJointComponent : public BaseJointComponent<SpringJoint, b2DistanceJointDef>
{
public:
	SpringJointComponent(Actor* owner, const std::wstring& kName);
	virtual ~SpringJointComponent() {};
	virtual void CreateJoint() override;


protected:
	virtual void SetDefaultProperties() override;



private:
	

};

