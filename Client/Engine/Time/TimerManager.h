#pragma once
#include <map>

#include "Singleton.h"
#include "Misc/DelegateMacros.h"
#include "Misc/Function.h"
#include <memory>

struct TimerData;
struct TimerHandle;

DECLARE_DELEGATE(TimerDelegate);
#pragma region MACRO
#define SET_TIMERBASE(rate, loop, delay)\
const float first_delay = delay >= 0.f ? delay : rate;\
data.loop = loop;\
data.rate = rate;\
data.expire_time = internal_time_ + first_delay;\
timers_.push_back(data);\
return data.handle;
#pragma endregion


struct TimerHandle
{
    TimerHandle() = delete;

    TimerHandle(TimerData& data)
        : addr_(reinterpret_cast<std::uintptr_t&>(data))
    {};

    const bool& operator==(const TimerHandle& input)
    {
        if (addr_ == input.addr_)
            return true;
        return false;
    }

    std::uintptr_t addr_;
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
    TimerHandle handle{ *this };
};

class TimerManager : public Singleton<TimerManager>
{
public:
    TimerManager();
    virtual ~TimerManager() override = default;
    void Tick(float delta_time);


    template<typename M>
    TimerHandle& SetTimer(M* target, void(M::* func)(void), float rate, bool loop = false, float delay = -1.f, typename std::enable_if<std::is_class<M>::value>::type* = nullptr);
    TimerHandle& SetTimer(Function<void(void)>&& func, float rate, bool loop = false, float delay = -1.f);
    TimerHandle& SetTimer(void(*func)(void), float rate, bool loop = false, float delay = -1.f);
    void ClearTimers();


    const bool FindTimer(const TimerHandle& input);
    inline float GetTime() const { return internal_time_; }

private:
    float internal_time_;
    std::vector<TimerData> timers_;
};

template<typename M>
inline TimerHandle& TimerManager::SetTimer(M* target, void(M::* func)(void), float rate, bool loop, float delay, typename std::enable_if<std::is_class<M>::value>::type*)
{
    TimerData data(std::move(Function<void(void)>(target, func)));
    SET_TIMERBASE(rate, loop, delay)
}