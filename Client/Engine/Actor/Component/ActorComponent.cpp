#include "pch.h"
#include "ActorComponent.h"

#include "../Actor.h"
#include "rttr/registration.h"
#include "rttr/detail/registration/registration_impl.h"

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

RTTR_REGISTRATION
{
    using namespace rttr;

    registration::class_<ActorComponent>("ActorComponent")
        .constructor<Actor*, const std::wstring&>();
}
