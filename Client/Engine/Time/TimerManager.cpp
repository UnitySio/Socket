#include "TimerManager.h"

TimerManager::TimerManager() :
    internal_time_(0.f)
{
}

void TimerManager::Tick(float delta_time)
{
    internal_time_ += delta_time;

    for (int i = 0; i < timers_.size(); i++)
    {
        if (internal_time_ >= timers_[i].expire_time)
        {
            timers_[i].callback();
            timers_.erase(timers_.begin() + i);
            i--;
        }
    }
}
