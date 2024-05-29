#include "TimerManager.h"

#include "Math/MathTypes.h"

TimerManager::TimerManager() :
    internal_time_(0.f)
{
}

void TimerManager::Tick(float delta_time)
{
    internal_time_ += delta_time;

    for (MathTypes::uint32 i = 0; i < timers_.size(); i++)
    {
        if (internal_time_ >= timers_[i].expire_time)
        {
            MathTypes::uint32 cell_count = timers_[i].loop ? static_cast<int>(trunc(internal_time_ - timers_[i].expire_time) / timers_[i].rate) + 1 : 1;
            for (MathTypes::uint32 j = 0; j < cell_count; j++)
            {
                timers_[i].callback();
            }

            if (timers_[i].loop)
            {
                timers_[i].expire_time += cell_count * timers_[i].rate;
            }
            else
            {
                timers_.erase(timers_.begin() + i);
                i--;
            }
        }
    }
}
