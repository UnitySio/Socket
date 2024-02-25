#pragma once

#include "../Singleton.h"

#include <windows.h>

// 초당 240회로 고정된 물리 시뮬레이션
#define FIXED_TIME_STEP (1.f / 240.f)

class Time : public Singleton<Time>
{
public:
    Time();
    virtual ~Time() override = default;
    
    void Init();
    void Tick();

    inline float GetFPS() const { return fps_; }

    static inline float DeltaTime() { return Get()->delta_time_ * Get()->time_scale_; }

private:
    LARGE_INTEGER frequency_;
    LARGE_INTEGER previous_count_;
    LARGE_INTEGER current_count_;

    float delta_time_;
    float time_scale_;
    float frame_count_;
    float frame_timer_;
    float fps_;
    
};