#pragma once
#include "Windows.h"

class Scene
{
public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void Begin() = 0;
    virtual void End() = 0;
    virtual void Tick(float deltaTime) = 0;
    virtual void Render() = 0;

    inline void SetName(const char* name) { strcpy_s(name_, name); }
    inline const char* GetName() const { return name_; }

private:
    char name_[256];
    
};
