#pragma once
#include "../Engine/Actor/Component/ActorComponent.h"
#include "../Engine/Math/Vector2.h"

class b2HingeJointDef;
class b2Body;
class b2HingeJoint;
class b2World;


class HingeJointComponent : public ActorComponent
{
public:
	HingeJointComponent(class Actor* owner, const std::wstring& kName);
	virtual ~HingeJointComponent() = default;


protected:
	virtual inline void InitializeComponent() override;
	virtual inline void UninitializeComponent() override;



private:
	b2HingeJointDef* jointDef_;
	b2HingeJoint* joint_;
	Actor* owner_;
	b2World* world_;



};

