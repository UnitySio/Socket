#include "Time.h"

LARGE_INTEGER Time::frequency_;
LARGE_INTEGER Time::previous_count_;

float Time::delta_time_ = 0.f;

Time::Time()
{
}

void Time::Init()
{
    QueryPerformanceFrequency(&frequency_);
    QueryPerformanceCounter(&previous_count_);
}

void Time::Tick()
{
    LARGE_INTEGER current_count;
    QueryPerformanceCounter(&current_count);

    delta_time_ = static_cast<float>(current_count.QuadPart - previous_count_.QuadPart) / static_cast<float>(frequency_.QuadPart);
    previous_count_ = current_count;
}
