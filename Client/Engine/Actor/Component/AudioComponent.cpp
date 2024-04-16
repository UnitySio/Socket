﻿#include "AudioComponent.h"

#include "TransformComponent.h"
#include "Math/Vector2.h"
#include "Actor/Actor.h"
#include "Audio/AudioManager.h"
#include "FMOD/fmod.h"

AudioComponent::AudioComponent(Actor* owner, const std::wstring& kName) :
    ActorComponent(owner, kName),
    sound_(nullptr),
    channel_(nullptr)
{
}

void AudioComponent::EndPlay(EndPlayReason type)
{
    ActorComponent::EndPlay(type);

    if (channel_)
    {
        FMOD_Channel_Stop(channel_);
        channel_ = nullptr;
    }
}

void AudioComponent::SetSound(FMOD_SOUND* sound)
{
    sound_ = sound;
    
    FMOD_Sound_SetMode(sound_, FMOD_3D);
    FMOD_Sound_Set3DMinMaxDistance(sound_, .1f, 100.f);
}

void AudioComponent::Play()
{
    if (!sound_) return;

    channel_ = AudioManager::PlaySound(sound_);
    
    const Math::Vector2 location = GetOwner()->GetTransform()->GetRelativeLocation();
    const FMOD_VECTOR sound_location = {location.x, location.y, 0.f};
    FMOD_Channel_Set3DAttributes(channel_, &sound_location, nullptr);
}
