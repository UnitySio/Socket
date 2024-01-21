#pragma once

#include "../Singleton.h"
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

class NetworkManager : public Singleton<NetworkManager>
{
public:
    NetworkManager();
    virtual ~NetworkManager() final = default;

    virtual void Release() final;
    
    bool Init();

private:
    
};
