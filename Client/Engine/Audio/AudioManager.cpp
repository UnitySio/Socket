﻿#include "AudioManager.h"

#include <ranges>

#include "FMOD/fmod.hpp"

AudioManager::AudioManager()
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

bool AudioManager::AddSound(const std::wstring& kName, const std::wstring& kPath)
{
    FMOD_SOUND* sound = nullptr;

    const std::string kPathStr(kPath.begin(), kPath.end());

    FMOD_RESULT result = FMOD_System_CreateSound(fmod_system_, kPathStr.c_str(), FMOD_DEFAULT, nullptr, &sound);
    if (result != FMOD_OK) return false;

    sound_map_[kName] = sound;
    return true;
}

void AudioManager::Tick()
{
    FMOD_System_Update(fmod_system_);
}

void AudioManager::SetLoop(FMOD_SOUND* sound, bool is_loop)
{
    FMOD_Sound_SetLoopCount(sound, is_loop ? -1 : 0);
}

void AudioManager::PlayOneShot(FMOD_SOUND* sound, float volume)
{
    FMOD_CHANNEL* channel = nullptr;
    FMOD_System_PlaySound(fmod_system_, sound, nullptr, false, &channel);
    if (channel) FMOD_Channel_SetVolume(channel, volume);
}

void AudioManager::PauseSound(FMOD_CHANNEL* channel)
{
    FMOD_Channel_SetPaused(channel, true);
}

void AudioManager::ResumeSound(FMOD_CHANNEL* channel)
{
    FMOD_Channel_SetPaused(channel, false);
}

void AudioManager::StopSound(FMOD_CHANNEL* channel)
{
    FMOD_Channel_Stop(channel);
}

FMOD_CHANNEL* AudioManager::PlaySound(FMOD_SOUND* sound, FMOD_CHANNELGROUP* channel_group)
{
    for (FMOD_CHANNEL* channel : channels_)
    {
        FMOD_BOOL is_playing = false;
        FMOD_Channel_IsPlaying(channel, &is_playing);

        if (!is_playing)
        {
            FMOD_System_PlaySound(fmod_system_, sound, channel_group, false, &channel);
            return channel;
        }
    }
    
    return nullptr;
}
