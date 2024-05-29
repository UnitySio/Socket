#pragma once
#include <functional>
#include <map>

#include "Singleton.h"

struct TimerHandle
{
};

struct TimerData
{
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
    void SetTimer(float time, T* obj, void(T::*func)());

    inline float GetTime() const { return internal_time_; }

private:
    float internal_time_;

    std::vector<TimerData> timers_;
    
};

template <typename T>
void TimerManager::SetTimer(float time, T* obj, void(T::* func)())
{
    TimerData data;
    data.expire_time = internal_time_ + time;
    data.callback = std::bind(func, obj);

    timers_.push_back(data);
}
