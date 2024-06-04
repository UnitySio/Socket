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

const TimerHandle& TimerManager::SetTimer(Function<void(void)>&& func, float rate, bool loop, float delay)
{
    TimerData data(std::move(Function<void(void)>(func)));
    SET_TIMERBASE(rate, loop, delay)
}

const TimerHandle& TimerManager::SetTimer(void(*func)(void), float rate, bool loop, float delay)
{
    TimerData data(std::move(Function<void(void)>(func)));
    SET_TIMERBASE(rate, loop, delay)
}

void TimerManager::ClearTimer(const TimerHandle& input)
{
    if (const TimerData* timer = FindTimer(input))
    {
        timers_.erase(std::find(timers_.begin(), timers_.end(), *timer));
    }
}

TimerData* TimerManager::FindTimer(const TimerHandle& input)
{
    for (auto& timer : timers_)
    {
        if (timer.handle == input)
        {
            return &timer;
        }
    }

    return nullptr;
}
