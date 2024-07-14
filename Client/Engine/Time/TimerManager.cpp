﻿#include "pch.h"
#include "TimerManager.h"

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

void TimerManager::ClearTimer(const TimerHandle& kHandle)
{
    TimerData* timer = FindTimer(kHandle);

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

void TimerManager::PauseTimer(const TimerHandle& kHandle)
{
    TimerData* timer = FindTimer(kHandle);
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

void TimerManager::UnPauseTimer(const TimerHandle& kHandle)
{
    TimerData* timer = FindTimer(kHandle);
    if (!timer || timer->status != TimerStatus::Paused) return;

    timer->expire_time += internal_time_;
    timer->status = TimerStatus::Active;
}

TimerData* TimerManager::FindTimer(const TimerHandle& kHandle)
{
    for (auto& timer : timers_)
    {
        if (timer.handle == kHandle)
        {
            return &timer;
        }
    }
    return nullptr;
}

float TimerManager::GetTimerElapsed(const TimerHandle& kHandle)
{
    TimerData* timer = FindTimer(kHandle);
    if (timer)
    {
        switch (timer->status)
        {
        case TimerStatus::Active:
        case TimerStatus::Executing:
            return timer->rate - (timer->expire_time - internal_time_);

        default:
            return timer->rate - timer->expire_time;
        }
    }
    
    return -1.f;
}

float TimerManager::GetTimerRemaining(const TimerHandle& kHandle)
{
    TimerData* timer = FindTimer(kHandle);
    if (timer)
    {
        switch (timer->status)
        {
        case TimerStatus::Active:
            return timer->expire_time - internal_time_;
            
        case TimerStatus::Executing:
            return 0.f;

        default:
            return timer->expire_time;
        }
    }
    
    return -1.f;
}

bool TimerManager::IsTimerActive(const TimerHandle& kHandle)
{
    TimerData* timer = FindTimer(kHandle);
    return timer && timer->status != TimerStatus::Paused;
}

bool TimerManager::IsTimerPaused(const TimerHandle& kHandle)
{
    TimerData* timer = FindTimer(kHandle);
    return timer && timer->status == TimerStatus::Paused;
}

void TimerManager::RemoveTimer(const TimerData& kTimer)
{
    timers_.erase(std::ranges::find(timers_, kTimer));
}
