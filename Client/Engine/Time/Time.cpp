﻿#include "Time.h"
#include "../Core.h"

Time::Time() :
    frequency_{},
    previous_count_{},
    current_count_{},
    delta_time_(0.f),
    time_scale_(10.f),
    frame_count_(0.f),
    frame_timer_(0.f),
    fps_(0.f)
{
}

void Time::Init()
{
    QueryPerformanceFrequency(&frequency_);
    QueryPerformanceCounter(&previous_count_);
}

void Time::Tick()
{
    QueryPerformanceCounter(&current_count_);

    delta_time_ = static_cast<float>(current_count_.QuadPart - previous_count_.QuadPart) / frequency_.QuadPart;
    previous_count_ = current_count_;

    // if (delta_time_ < (1.f / 60.f)) delta_time_ = 1.f / 60.f;

    frame_count_++;
    frame_timer_ += delta_time_;

    if (frame_timer_ >= 1.f)
    {
        fps_ = frame_count_;
        
        frame_count_ = 0.f;
        frame_timer_ = 0.f;
    }
}