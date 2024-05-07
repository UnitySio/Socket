#include "Time.h"

#include "Windows/WindowsApplication.h"

float Time::frequency_ = 0.f;

Time::Time()
{
}

float Time::Init()
{
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    frequency_ = 1.f / frequency.QuadPart;

    return Seconds();
}

float Time::Seconds()
{
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return static_cast<float>(count.QuadPart) * frequency_;
}
