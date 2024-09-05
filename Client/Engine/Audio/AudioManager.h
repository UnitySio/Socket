#pragma once
#include <map>

#include "Singleton.h"

#define MAX_CHANNEL_COUNT 4095

class Audio;
class FMOD_SOUND;
class FMOD_CHANNEL;
class FMOD_CHANNELGROUP;
class SceneComponent;

class AudioManager : public Singleton<AudioManager>
{
public:
    AudioManager();
    virtual ~AudioManager() override;

    void PlayOneShot(const Audio* audio, float volume = 1.f);
    void PauseSound(int id);
    void ResumeSound(int id);
    void StopSound(int id);
    void StopAllSounds();
    void SetVolume(int id, int volume);
    void SetMute(int id, bool is_mute);
    void SetAllMutes(bool is_mute);

    int PlaySound2D(const Audio* audio, FMOD_CHANNELGROUP* channel_group = nullptr);

private:
    friend class Audio;
    friend class GameEngine;
    
    bool Init();
    
    void Tick();
    
    class FMOD_SYSTEM* fmod_system_;
    FMOD_CHANNEL* channels_[MAX_CHANNEL_COUNT];
    
};
