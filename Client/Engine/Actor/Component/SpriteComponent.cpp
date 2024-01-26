#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(Actor* owner) :
    Component(owner),
    sprite_(nullptr)
{
}

void SpriteComponent::Render()
{
}
