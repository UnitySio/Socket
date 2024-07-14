#include "pch.h"
#include "ActorComponent.h"

#include "../Actor.h"

ActorComponent::ActorComponent(Actor* owner, const std::wstring& kName) : owner_(owner)
{
    name_ = kName;
}
