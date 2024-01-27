#include "ActorComponent.h"

ActorComponent::ActorComponent(Actor* owner, const std::wstring& name) : owner_(owner)
{
    name_ = name;
}
