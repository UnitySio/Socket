﻿#include "AudioListenerComponent.h"

#include "TransformComponent.h"
#include "Math/Vector2.h"
#include "Actor/Actor.h"
#include "Audio/AudioManager.h"
#include "FMOD/fmod.h"
#include "FMOD/fmod_common.h"

AudioListenerComponent::AudioListenerComponent(Actor* owner, const std::wstring& kName) :
    ActorComponent(owner, kName)
{
}

void AudioListenerComponent::TickComponent(float delta_time)
{
    ActorComponent::TickComponent(delta_time);

    const Math::Vector2 position = GetOwner()->GetTransform()->GetWorldPosition();
    const FMOD_VECTOR sound_position = {position.x, position.y, 0.f};
    FMOD_System_Set3DListenerAttributes(AudioManager::Get()->fmod_system_, 0, &sound_position, nullptr, nullptr, nullptr);
}
