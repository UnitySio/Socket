#pragma once
#include <map>

#include "Singleton.h"
#include "Misc/DelegateMacros.h"
#include "Misc/Function.h"
DECLARE_DELEGATE(TimerDelegate);
#pragma region MACRO
#define SET_TIMERBASE(rate, loop, delay)\
const float first_delay = delay >= 0.f ? delay : rate;\
TimerHandle new_handle;\
data.loop = loop;\
data.rate = rate;\
data.expire_time = internal_time_ + first_delay;\
data.handle = new_handle;\
handle = new_handle;\
timers_.push_back(data);
#pragma endregion


struct TimerHandle
{
    auto GetHandle() -> decltype(nullptr)
    {
        return nullptr;
    }
};

struct TimerData
{
    TimerData() = delete;

    TimerData(Function<void(void)>&& func) 
        : callback(std::forward<Function<void(void)>>(func)), loop(false), rate(0.0f), expire_time(0.0f)
    {};

    template<typename M>
    TimerData(M* target, Function<void(void)>&& func)
        : callback(std::forward<Function<void(void)>>(target, func)), loop(false), rate(0.0f), expire_time(0.0f)
    {};


    bool loop;
    float rate;
    double expire_time;
    Function<void(void)> callback;
    TimerHandle handle;
};

class TimerManager : public Singleton<TimerManager>
{
public:
    TimerManager();
    virtual ~TimerManager() override = default;
    void Tick(float delta_time);


    template<typename M>
    void SetTimer(TimerHandle& handle, M* target, void(M::* func)(void), float rate, bool loop = false, float delay = -1.f, typename std::enable_if<std::is_class<M>::value>::type* = nullptr);
    void SetTimer(TimerHandle& handle, Function<void(void)>&& func, float rate, bool loop = false, float delay = -1.f);
    void SetTimer(TimerHandle& handle, void(*func)(void), float rate, bool loop = false, float delay = -1.f);
    void TimerClear();

    
    inline float GetTime() const { return internal_time_; }

private:
    float internal_time_;
    std::vector<TimerData> timers_;
};

template<typename M>
inline void TimerManager::SetTimer(TimerHandle& handle, M* target, void(M::* func)(void), float rate, bool loop, float delay, typename std::enable_if<std::is_class<M>::value>::type*)
{
    TimerData data(std::move(Function<void(void)>(target, func)));
    SET_TIMERBASE(rate, loop, delay)
}