#pragma once
#include <vector>

#include "Singleton.h"

class Scene : public Singleton<Scene>
{
public:
    Scene();
    virtual ~Scene() final = default;

    virtual void Release() final;

    void Tick(float delta_time);
    void Render();
    void AddLog(std::string format, ...);

private:
    std::vector<std::string> logs_;

    char input_buffer_[1024];
    
};
