#pragma once
#include "ActorComponent.h"

class FMOD_SOUND;

class AudioComponent : public ActorComponent
{
public:
    AudioComponent(class Actor* owner, const std::wstring& kName);
    virtual ~AudioComponent() override = default;

    void SetSound(FMOD_SOUND* sound);
    void Play();

private:
    FMOD_SOUND* sound_;
    class FMOD_CHANNEL* channel_;
    
};
