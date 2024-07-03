﻿#include "TimerManager.h"

#include "Math/MathTypes.h"

TimerManager::TimerManager() :
    internal_time_(0.f)
{
}

void TimerManager::Tick(float delta_time)
{
    internal_time_ += delta_time;

    for (auto it = timers_.begin(); it != timers_.end();)
    {
        TimerData& timer = *it;
    
        if (timer.status == TimerStatus::Removal)
        {
            it = timers_.erase(it);
            continue;
        }

        if (timer.status == TimerStatus::Active && internal_time_ >= timer.expire_time)
        {
            timer.status = TimerStatus::Executing;
        
            MathTypes::uint32 cell_count = timer.loop ? static_cast<int>(trunc(internal_time_ - timer.expire_time) / timer.rate) + 1 : 1;
            for (MathTypes::uint32 i = 0; i < cell_count; ++i)
            {
                timer.callback();
            }

            if (timer.loop)
            {
                timer.expire_time += timer.rate * cell_count;
                timer.status = TimerStatus::Active;
                ++it;
            }
            else
            {
                it = timers_.erase(it);
            }
        }
        else
        {
            ++it;
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

void TimerManager::ClearTimer(const TimerHandle& kInput)
{
    TimerData* timer = FindTimer(kInput);

    switch (timer->status)
    {
    case TimerStatus::Active:
        {
            timer->status = TimerStatus::Removal;
        }
        break;

    case TimerStatus::Executing:
    case TimerStatus::Paused:
        {
            RemoveTimer(*timer);
        }
        break;
    }
}

void TimerManager::PauseTimer(const TimerHandle& kInput)
{
    TimerData* timer = FindTimer(kInput);
    if (!timer || timer->status == TimerStatus::Paused) return;

    if (timer->status == TimerStatus::Executing && !timer->loop)
    {
        RemoveTimer(*timer);
    }
    else
    {
        timer->status = TimerStatus::Paused;
        timer->expire_time -= internal_time_;
    }
}

void TimerManager::UnPauseTimer(const TimerHandle& kInput)
{
    TimerData* timer = FindTimer(kInput);
    if (!timer || timer->status != TimerStatus::Paused) return;

    timer->expire_time += internal_time_;
    timer->status = TimerStatus::Active;
}

TimerData* TimerManager::FindTimer(const TimerHandle& kInput)
{
    for (auto& timer : timers_)
    {
        if (timer.handle == kInput)
        {
            return &timer;
        }
    }
    return nullptr;
}

void TimerManager::RemoveTimer(const TimerData& kTimer)
{
    timers_.erase(std::find(timers_.begin(), timers_.end(), kTimer));
}
