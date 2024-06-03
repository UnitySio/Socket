#pragma once
#include <functional>
#include <map>

#include "Singleton.h"
#include "Misc/DelegateMacros.h"

DECLARE_DELEGATE(TimerDelegate);

struct TimerHandle
{
};

struct CallbackFunction;

struct TimerData
{
    bool loop;
    float rate;
    double expire_time;
    std::function<void()> callback;
    CallbackFunction* callbackDummy;
    TimerHandle handle;
};

class TimerManager : public Singleton<TimerManager>
{
public:
    TimerManager();
    virtual ~TimerManager() override = default;

    void Tick(float delta_time);

    template<typename T>
    void SetTimer(TimerHandle& handle, T* obj, void(T::*method)(), Function<void(void)> func, float rate, bool loop = false, float delay = -1.f);

    inline float GetTime() const { return internal_time_; }

private:
    float internal_time_;

    std::vector<TimerData> timers_;
    
};

template <typename T>
void TimerManager::SetTimer(TimerHandle& handle, T* obj, void(T::* method)(), Function<void(void)> func, float rate, bool loop, float delay)
{
    const float first_delay = delay >= 0.f ? delay : rate;
    
    TimerHandle new_handle;
    
    TimerData data;
    data.loop = loop;
    data.rate = rate;
    data.expire_time = internal_time_ + first_delay;
    data.callback = std::bind(method, obj);
    data.callbackDummy = func;
    data.handle = new_handle;

    handle = new_handle;
    timers_.push_back(data);
}


struct CallbackFunction
{
    virtual std::any GetFunc() = 0;
};

template<typename Ret, typename... Args>
struct IFunction : public CallbackFunction
{
    virtual std::any GetFunc() override
    {
        return func_;
    }

    Function<Ret(Args...)> func_;
};