#include "HingeJointComponent.h"
#include "box2d/box2d.h"

HingeJointComponent::HingeJointComponent(Actor* owner, const std::wstring& kName):
	ActorComponent(owner, kName)
{
	
}

inline void HingeJointComponent::InitializeComponent()
{
}

inline void HingeJointComponent::UninitializeComponent()
{
}
