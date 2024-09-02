#pragma once
#include <map>

#include "Singleton.h"

#define MAX_CHANNEL_COUNT 4095

class FMOD_SOUND;
class FMOD_CHANNEL;
class FMOD_CHANNELGROUP;
class SceneComponent;

class AudioManager : public Singleton<AudioManager>
{
public:
    AudioManager();
    virtual ~AudioManager() override;

    bool LoadSound(const std::wstring& kName, const std::wstring& kPath);

    void SetLoop(const std::wstring& kName, bool is_loop);
    void PlayOneShot(const std::wstring& kName, float volume = 1.f);
    void PauseSound(int id);
    void ResumeSound(int id);
    void StopSound(int id);
    void StopAllSounds();
    void SetVolume(int id, int volume);
    void SetMute(int id, bool is_mute);
    void SetAllMutes(bool is_mute);

    int PlaySound2D(const std::wstring& kName, FMOD_CHANNELGROUP* channel_group = nullptr);

private:
    friend class GameEngine;
    
    bool Init();
    
    void Tick();
    
    class FMOD_SYSTEM* fmod_system_;
    FMOD_CHANNEL* channels_[MAX_CHANNEL_COUNT];

    std::map<std::wstring, FMOD_SOUND*> sound_map_;
    
};
