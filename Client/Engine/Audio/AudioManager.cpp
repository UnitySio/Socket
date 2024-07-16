#include "pch.h"
#include "AudioManager.h"

#include <ranges>

#include "FMOD/fmod.hpp"

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

bool AudioManager::AddSound(const std::wstring& kName, const std::wstring& kPath)
{
    FMOD_SOUND* sound = nullptr;

    const std::wstring kFinalPath = L".\\Game_Data\\" + kPath;
    const std::string kFinalPathStr(kFinalPath.begin(), kFinalPath.end());

    FMOD_RESULT result = FMOD_System_CreateSound(Get()->fmod_system_, kFinalPathStr.c_str(), FMOD_DEFAULT, nullptr, &sound);
    if (result != FMOD_OK) return false;

    Get()->sound_map_[kName] = sound;
    return true;
}

void AudioManager::Tick()
{
    FMOD_System_Update(Get()->fmod_system_);
}

void AudioManager::SetLoop(FMOD_SOUND* sound, bool is_loop)
{
    // FMOD_MODE mode;
    // FMOD_Sound_GetMode(sound, &mode);
    //
    // if (is_loop) mode |= FMOD_LOOP_NORMAL;
    // else mode &= ~FMOD_LOOP_NORMAL;
    //
    // FMOD_Sound_SetMode(sound, mode);
}

void AudioManager::PlayOneShot(FMOD_SOUND* sound, float volume)
{
    FMOD_CHANNEL* channel = nullptr;
    FMOD_System_PlaySound(Get()->fmod_system_, sound, nullptr, false, &channel);
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
    for (FMOD_CHANNEL* channel : Get()->channels_)
    {
        FMOD_BOOL is_playing = false;
        FMOD_Channel_IsPlaying(channel, &is_playing);

        if (!is_playing)
        {
            FMOD_System_PlaySound(Get()->fmod_system_, sound, channel_group, false, &channel);
            return channel;
        }
    }
    
    return nullptr;
}
