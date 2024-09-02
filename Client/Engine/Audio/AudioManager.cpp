#include "pch.h"
#include "AudioManager.h"

#include <ranges>

#include "FMOD/fmod.hpp"
#include "Math/Math.h"

AudioManager::AudioManager() :
    fmod_system_(nullptr),
    channels_(),
    sound_map_()
{
}

AudioManager::~AudioManager()
{
    for (const auto& kSound : sound_map_ | std::views::values)
    {
        FMOD_Sound_Release(kSound);
    }
    
    FMOD_System_Close(fmod_system_);
    FMOD_System_Release(fmod_system_);
}

bool AudioManager::Init()
{
    FMOD_RESULT result = FMOD_System_Create(&fmod_system_, FMOD_VERSION);
    if (result != FMOD_OK) return false;

    result = FMOD_System_Init(fmod_system_, MAX_CHANNEL_COUNT, FMOD_INIT_NORMAL, nullptr);
    return result == FMOD_OK;
}

bool AudioManager::LoadSound(const std::wstring& kName, const std::wstring& kPath)
{
    if (sound_map_.contains(kName)) return false;
    
    FMOD_SOUND* sound = nullptr;

    const std::string kFinalPath(kPath.begin(), kPath.end());

    FMOD_RESULT result = FMOD_System_CreateSound(fmod_system_, kFinalPath.c_str(), FMOD_DEFAULT, nullptr, &sound);
    if (result != FMOD_OK) return false;

    sound_map_[kName] = sound;
    return true;
}

void AudioManager::Tick()
{
    FMOD_System_Update(fmod_system_);
}

void AudioManager::SetLoop(const std::wstring& kName, bool is_loop)
{
    const auto it = sound_map_.find(kName);
    if (it == sound_map_.end()) return;
    
    FMOD_MODE mode;
    FMOD_Sound_GetMode(it->second, &mode);

    if (is_loop)
    {
        mode &= ~FMOD_LOOP_OFF;
        mode |= FMOD_LOOP_NORMAL;
    }
    else
    {
        mode &= ~FMOD_LOOP_NORMAL;
        mode |= FMOD_LOOP_OFF;
    }

    FMOD_Sound_SetMode(it->second, mode);
}

void AudioManager::PlayOneShot(const std::wstring& kName, float volume)
{
    const auto it = sound_map_.find(kName);
    if (it == sound_map_.end()) return;
    
    FMOD_CHANNEL* channel = nullptr;
    FMOD_System_PlaySound(fmod_system_, it->second, nullptr, false, &channel);
    if (channel) FMOD_Channel_SetVolume(channel, volume);
}

void AudioManager::PauseSound(int id)
{
    if (id < 0 || id >= MAX_CHANNEL_COUNT) return;
    FMOD_Channel_SetPaused(channels_[id], true);
}

void AudioManager::ResumeSound(int id)
{
    if (id < 0 || id >= MAX_CHANNEL_COUNT) return;
    FMOD_Channel_SetPaused(channels_[id], false);
}

void AudioManager::StopSound(int id)
{
    if (id < 0 || id >= MAX_CHANNEL_COUNT) return;
    FMOD_Channel_Stop(channels_[id]);
}

void AudioManager::StopAllSounds()
{
    for (const auto& channel : channels_)
    {
        FMOD_Channel_Stop(channel);
    }
}

void AudioManager::SetVolume(int id, int volume)
{
    if (id < 0 || id >= MAX_CHANNEL_COUNT) return;
    volume = Math::Clamp(volume, 0.f, 100.f);
    
    const float final_volume = volume / 100.f;
    FMOD_Channel_SetVolume(channels_[id], final_volume);
}

void AudioManager::SetMute(int id, bool is_mute)
{
    if (id < 0 || id >= MAX_CHANNEL_COUNT) return;
    FMOD_Channel_SetMute(channels_[id], is_mute);
}

void AudioManager::SetAllMutes(bool is_mute)
{
    for (const auto& channel : channels_)
    {
        FMOD_Channel_SetMute(channel, is_mute);
    }
}

int AudioManager::PlaySound2D(const std::wstring& kName, FMOD_CHANNELGROUP* channel_group)
{
    const auto it = sound_map_.find(kName);
    if (it == sound_map_.end()) return -1;

    for (int i = 0; i < MAX_CHANNEL_COUNT; ++i)
    {
        FMOD_CHANNEL* channel = channels_[i];
        FMOD_BOOL is_playing = false;
        FMOD_Channel_IsPlaying(channel, &is_playing);
        
        if (!is_playing)
        {
            FMOD_System_PlaySound(fmod_system_, it->second, channel_group, false, &channels_[i]);
            return i;
        }
    }

    return -1;
}
