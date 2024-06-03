#pragma once
#include <map>

#include "Singleton.h"
#include "Misc/DelegateMacros.h"
#include "Misc/Function.h"
DECLARE_DELEGATE(TimerDelegate);

struct TimerHandle
{

};

struct TimerData
{
    TimerData(Function<void(void)> func) 
        : callback(func), loop(false), rate(0.0f), expire_time(0.0f)
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

    void SetTimer(TimerHandle& handle, Function<void(void)>&& func, float rate, bool loop = false, float delay = -1.f);
    void TimerClear();
    void SetTick(TimerHandle& handle, Function<void(void)>&& func);
    void TickClear();
    
    inline float GetTime() const { return internal_time_; }

private:
    float internal_time_;
    std::vector<TimerData> timers_;
    std::vector<Function<void(void)>> ticks_;
    void MTest(int a, int b);
};




void GTest(int a, int b, int c);