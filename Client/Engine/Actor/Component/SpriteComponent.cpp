#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(Actor* owner, const std::wstring& name) :
    ActorComponent(owner, name),
    sprite_(nullptr)
{
}

void SpriteComponent::Render()
{
}
