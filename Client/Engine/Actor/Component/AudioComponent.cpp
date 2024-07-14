#include "pch.h"
#include "AudioComponent.h"

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

    FMOD_BOOL is_playing = false;
    if (channel_)
    {
        FMOD_Channel_IsPlaying(channel_, &is_playing);
        if (!is_playing) return;
        
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
    
    const Math::Vector2 position = GetOwner()->GetTransform()->GetWorldPosition();
    const FMOD_VECTOR sound_position = {position.x, position.y, 0.f};
    FMOD_Channel_Set3DAttributes(channel_, &sound_position, nullptr);
}
