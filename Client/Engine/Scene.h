#pragma once
#include "Singleton.h"
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

class Scene : public Singleton<Scene>
{
public:
    Scene();
    virtual ~Scene() final = default;
    
    void Tick(float delta_time);
    void Render();
};