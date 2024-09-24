#include "pch.h"
#include "ActorComponent.h"

#include "../Actor.h"

ActorComponent::ActorComponent(Actor* owner, const std::wstring& kName) :
    owner_(owner),
    has_begun_play_(false)
{
    name_ = kName;
}

void ActorComponent::BeginPlay()
{
    has_begun_play_ = true;
}
