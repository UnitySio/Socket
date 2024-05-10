#pragma once
#include <vector>

struct TimerHandle
{
};

struct TimerData
{
};

class TimerManager
{
public:
    TimerManager();
    ~TimerManager() = default;

    void Tick(float deltaTime);
    void SetTimer(TimerHandle& handle);
    void ClearTimer(TimerHandle& handle);

private:
    float internal_time_;

    std::vector<TimerData> timers_;
    
};
