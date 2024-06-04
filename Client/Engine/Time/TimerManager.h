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
    TimerData() = delete;
    TimerData(Function<void(void)>&& func) 
        : callback(std::forward<Function<void(void)>>(func)), loop(false), rate(0.0f), expire_time(0.0f)
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

    /*template<typename Ret, typename... Args>
    template<Ret(Args...)>*/
    
    
    void TimerClear();
    
    
    inline float GetTime() const { return internal_time_; }

private:
    float internal_time_;
    std::vector<TimerData> timers_;
    void MTest(int a, int b);
};




void GTest(const std::wstring& kstr);