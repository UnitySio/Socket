#include "TimerManager.h"

#include "Math/MathTypes.h"

TimerManager::TimerManager() :
    internal_time_(0.f)
{

    TimerHandle handle;
    SetTimer(handle, this, &TimerManager::Test, 1.0f);
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


void TimerManager::SetTimer(TimerHandle& handle, Function<void(void)>&& func, float rate, bool loop, float delay)
{
    const float first_delay = delay >= 0.f ? delay : rate;

    TimerHandle new_handle;

    TimerData data(std::move(Function<void(void)>(func)));
    data.loop = loop;
    data.rate = rate;
    data.expire_time = internal_time_ + first_delay;
    data.handle = new_handle;

    handle = new_handle;
    timers_.push_back(data);
}

void TimerManager::SetTimer(TimerHandle& handle, void(*func)(void), float rate, bool loop, float delay)
{
    const float first_delay = delay >= 0.f ? delay : rate;

    TimerHandle new_handle;

    
    TimerData data(std::move(Function<void(void)>(func)));

    data.loop = loop;
    data.rate = rate;
    data.expire_time = internal_time_ + first_delay;
    data.handle = new_handle;


    handle = new_handle;
    timers_.push_back(data);
}

void TimerManager::TimerClear()
{
    timers_.clear();
}

void TimerManager::Test()
{
    int a = 10;
    auto temp = a;
}