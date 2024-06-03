#include "TimerManager.h"

#include "Math/MathTypes.h"

TimerManager::TimerManager() :
    internal_time_(0.f)
{
    TimerHandle handle;
    Function<void(void)> f(this, &TimerManager::MTest, 3, 5);
    SetTimer(handle, std::move(f), 1.0f);
    Function<void(void)> f2(&GTest, 10, 20);
    SetTimer(handle, std::move(f2), 2.0f);

    int a = 10;
    int b = 10;
    Function<void(void)> f3([a, b]() {auto temp = a + b; });
    SetTick(handle, std::move(f3));
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

    ///////////// Propose //////////////
    for (const auto& temp : ticks_)
    {
        temp();
    }
}


void TimerManager::SetTimer(TimerHandle& handle, Function<void(void)>&& func, float rate, bool loop, float delay)
{
    const float first_delay = delay >= 0.f ? delay : rate;

    TimerHandle new_handle;

    TimerData data(func);
    data.loop = loop;
    data.rate = rate;
    data.expire_time = internal_time_ + first_delay;
    data.handle = new_handle;

    handle = new_handle;
    timers_.push_back(data);
}

void TimerManager::SetTick(TimerHandle& handle, Function<void(void)>&& func)
{
    ticks_.push_back(std::forward<Function<void(void)>>(func));
}

void TimerManager::MTest(int a, int b)
{
    auto temp = a + b;
}

void GTest(int a, int b)
{
    auto temp = a + b;
}
