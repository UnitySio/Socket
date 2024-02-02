#include "ActorComponent.h"

#include "../Actor.h"

ActorComponent::ActorComponent(Actor* owner, const std::wstring& kName) : owner_(owner)
{
    name_ = kName;
}

b2World* ActorComponent::GetWorld() const
{
    return owner_->GetWorld();
}
