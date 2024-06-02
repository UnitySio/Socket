#pragma once
#include <functional>
#include <map>

#include "Singleton.h"
#include "Misc/DelegateMacros.h"

DECLARE_DELEGATE(TimerDelegate);

struct TimerHandle
{
};

struct TimerData
{
    bool loop;
    float rate;
    double expire_time;
    std::function<void()> callback;
    TimerHandle handle;
};

class TimerManager : public Singleton<TimerManager>
{
public:
    TimerManager();
    virtual ~TimerManager() override = default;

    void Tick(float delta_time);

    template<typename T>
    void SetTimer(TimerHandle& handle, T* obj, void(T::*method)(), float rate, bool loop = false, float delay = -1.f);

    inline float GetTime() const { return internal_time_; }

private:
    float internal_time_;

    std::vector<TimerData> timers_;
    
};

template <typename T>
void TimerManager::SetTimer(TimerHandle& handle, T* obj, void(T::* method)(), float rate, bool loop, float delay)
{
    const float first_delay = delay >= 0.f ? delay : rate;
    
    TimerHandle new_handle;
    
    TimerData data;
    data.loop = loop;
    data.rate = rate;
    data.expire_time = internal_time_ + first_delay;
    data.callback = std::bind(method, obj);
    data.handle = new_handle;

    handle = new_handle;
    timers_.push_back(data);
}
