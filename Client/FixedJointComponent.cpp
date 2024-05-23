#include "FixedJointComponent.h"

FixedJointComponent::FixedJointComponent(Actor* owner, const std::wstring& kName):
	BaseJointComponent(owner, kName),
	owner_(owner)
{
}

inline void FixedJointComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

inline void FixedJointComponent::UninitializeComponent()
{
	Super::UninitializeComponent();
}
