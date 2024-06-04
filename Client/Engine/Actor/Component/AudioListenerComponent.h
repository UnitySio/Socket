#pragma once
#include "ActorComponent.h"

class AudioListenerComponent : public ActorComponent
{
public:
    AudioListenerComponent(class Actor* owner, const std::wstring& kName);
    virtual ~AudioListenerComponent() override = default;

    virtual void TickComponent(float delta_time) override;
    
};
