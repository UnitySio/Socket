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

    bool Init();
    bool AddSound(const std::wstring& kName, const std::wstring& kPath);

    static void Tick();
    static void SetLoop(FMOD_SOUND* sound, bool is_loop);
    static void PlayOneShot(FMOD_SOUND* sound, float volume = 1.f);
    static void PauseSound(FMOD_CHANNEL* channel);
    static void ResumeSound(FMOD_CHANNEL* channel);
    static void StopSound(FMOD_CHANNEL* channel);

    static FMOD_CHANNEL* PlaySound(FMOD_SOUND* sound, FMOD_CHANNELGROUP* channel_group = nullptr);

    static FMOD_SOUND* GetSound(const std::wstring& kName) { return Get()->sound_map_.at(kName); }

    static inline void SetListener(SceneComponent* listener) { Get()->listener_ = listener; }

private:
    friend class AudioComponent;
    
    class FMOD_SYSTEM* fmod_system_;
    FMOD_CHANNEL* channels_[MAX_CHANNEL_COUNT];

    std::map<std::wstring, FMOD_SOUND*> sound_map_;

    SceneComponent* listener_;
    
};
