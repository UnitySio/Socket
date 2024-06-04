#pragma once
#include "Singleton.h"
#include "Misc/DelegateMacros.h"
#include "Misc/Function.h"

struct TimerData;
struct TimerHandle;

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

    bool operator==(const TimerHandle& input) const
    {
        return addr_ == input.addr_;
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
    const TimerHandle& SetTimer(M* target, void(M::* func)(void), float rate, bool loop = false, float delay = -1.f, typename std::enable_if<std::is_class<M>::value>::type* = nullptr);
    template<typename M>
    const TimerHandle& SetTimer(M* target, void(M::* func)(void) const, float rate, bool loop = false, float delay = -1.f, typename std::enable_if<std::is_class<M>::value>::type* = nullptr);
    template<typename L>
    const TimerHandle& SetTimer(L&& lambda, float rate, bool loop = false, float delay = -1.f);
    const TimerHandle& SetTimer(Function<void(void)>&& func, float rate, bool loop = false, float delay = -1.f);
    const TimerHandle& SetTimer(void(*func)(void), float rate, bool loop = false, float delay = -1.f);
    
    void ClearTimers();
    bool FindTimer(const TimerHandle& input) const;

    inline float GetTime() const { return internal_time_; }
private:
    float internal_time_;
    std::vector<TimerData> timers_;
};

template<typename M>
inline const TimerHandle& TimerManager::SetTimer(M* target, void(M::* func)(void), float rate, bool loop, float delay, typename std::enable_if<std::is_class<M>::value>::type*)
{
    TimerData data(std::move(Function<void(void)>(target, func)));
    SET_TIMERBASE(rate, loop, delay)
}

template<typename M>
inline const TimerHandle& TimerManager::SetTimer(M* target, void(M::* func)(void) const, float rate, bool loop, float delay, typename std::enable_if<std::is_class<M>::value>::type*)
{
    TimerData data(std::move(Function<void(void)>(target, func)));
    SET_TIMERBASE(rate, loop, delay)
}

template<typename L>
inline const TimerHandle& TimerManager::SetTimer(L&& lambda, float rate, bool loop, float delay)
{
    TimerData data(std::move(Function<void(void)>(std::move(lambda))));
    SET_TIMERBASE(rate, loop, delay)
}
