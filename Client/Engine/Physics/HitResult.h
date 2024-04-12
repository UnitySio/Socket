#pragma once

struct HitResult
{
    float Distance;
    
    Vector Location;
    Vector Normal;
    Vector TraceStart;
    Vector TraceEnd;
    
    class Actor* Actor;
};
