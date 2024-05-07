#include "Time.h"

LARGE_INTEGER Time::previous_count_;

float Time::second_per_count_ = 0.f;
float Time::delta_time_ = 0.f;

Time::Time()
{
}

void Time::Init()
{
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    second_per_count_ = 1.f / static_cast<float>(frequency.QuadPart);
    
    QueryPerformanceCounter(&previous_count_);
}

void Time::Tick()
{
    LARGE_INTEGER current_count;
    QueryPerformanceCounter(&current_count);

    delta_time_ = static_cast<float>(current_count.QuadPart - previous_count_.QuadPart) * second_per_count_;
    previous_count_ = current_count;
}

float Time::Seconds()
{
    LARGE_INTEGER current_count;
    QueryPerformanceCounter(&current_count);

    return static_cast<float>(current_count.QuadPart) * second_per_count_;
}
