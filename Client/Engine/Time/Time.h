#pragma once

#include <Windows.h>

class Time
{
public:
    Time();
    ~Time() = default;

    static void Init();
    static void Tick();

    static float Seconds();
    
    inline static float DeltaTime() { return delta_time_; }

private:
    static LARGE_INTEGER previous_count_;

    static float second_per_count_;
    static float delta_time_;
    
};
