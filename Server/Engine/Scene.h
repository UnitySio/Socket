#pragma once
#include <vector>

#include "Singleton.h"

#include <WinSock2.h>

#pragma comment(lib, "ws2_32")

class Scene : public Singleton<Scene>
{
public:
    Scene();
    virtual ~Scene() final = default;

    virtual void Release() final;
    
    void Tick(float delta_time);
    void Render();

private:
    void AddLog(std::string format, ...);

    std::vector<std::string> logs_;

    char input_buffer_[1024];
    
    SOCKET server_socket_;
    
};