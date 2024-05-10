#include "TimerManager.h"

TimerManager::TimerManager() :
    internal_time_(0.f),
    timers_()
{
}

void TimerManager::Tick(float deltaTime)
{
    internal_time_ += deltaTime;
}

void TimerManager::SetTimer(TimerHandle& handle)
{
}

void TimerManager::ClearTimer(TimerHandle& handle)
{
}
