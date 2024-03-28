#pragma once
#include <map>

#include "Singleton.h"

#define MAX_CHANNEL_COUNT 4095

class FMOD_SOUND;
class FMOD_CHANNEL;
class FMOD_CHANNELGROUP;

class AudioManager : public Singleton<AudioManager>
{
public:
    AudioManager();
    virtual ~AudioManager() override;

    bool Init();
    bool AddSound(const std::wstring& kName, const std::wstring& kPath);

    void Tick();
    void SetLoop(FMOD_SOUND* sound, bool is_loop);
    void PlayOneShot(FMOD_SOUND* sound, float volume = 1.f);
    void PauseSound(FMOD_CHANNEL* channel);
    void ResumeSound(FMOD_CHANNEL* channel);
    void StopSound(FMOD_CHANNEL* channel);

    FMOD_CHANNEL* PlaySound(FMOD_SOUND* sound, FMOD_CHANNELGROUP* channel_group = nullptr);

    FMOD_SOUND* GetSound(const std::wstring& kName) const { return sound_map_.at(kName); }

private:
    class FMOD_SYSTEM* fmod_system_;
    FMOD_CHANNEL* channels_[MAX_CHANNEL_COUNT];

    std::map<std::wstring, FMOD_SOUND*> sound_map_;
    
};
