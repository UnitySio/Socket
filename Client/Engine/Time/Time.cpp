#include "Time.h"

#include <iostream>

#include "Core.h"

Time::Time() :
    frequency_{},
    previous_count_{},
    current_count_{},
    delta_time_(0.f),
    time_scale_(1.f),
    frame_count_(0.f),
    frame_timer_(0.f),
    fps_(0.f)
{
}

void Time::Init()
{
    QueryPerformanceFrequency(&frequency_);
    QueryPerformanceCounter(&previous_count_);
    QueryPerformanceCounter(&start_count_);
}

void Time::Tick()
{
    QueryPerformanceCounter(&current_count_);
    
    delta_time_ = static_cast<float>(current_count_.QuadPart - previous_count_.QuadPart) / frequency_.QuadPart;
    previous_count_ = current_count_;
    
    frame_count_++;
    frame_timer_ += delta_time_;
    
    if (frame_timer_ >= 1.f)
    {
        fps_ = frame_count_;

        const float kMS = 1000.f / fps_;

        WCHAR buffer[256];
        swprintf_s(buffer, L"Game - FPS: %.f(%.fms)", fps_, kMS);
        SetWindowText(Core::Get()->GetWindowHandle(), buffer);
        
        frame_count_ = 0.f;
        frame_timer_ = 0.f;
    }

    // constexpr float limit = 1.f / 60.f;
    // if (delta_time_ < limit)
    // {
    //     const DWORD sleep_time = static_cast<DWORD>((limit - delta_time_) * 1000.f);
    //     Sleep(sleep_time);
    // }
}

float Time::RealTime()
{
    QueryPerformanceCounter(&Get()->end_count_);
    return static_cast<float>(Get()->end_count_.QuadPart - Get()->start_count_.QuadPart) / Get()->frequency_.QuadPart;
}
