#pragma once
#include "../Singleton.h"

class NetworkManager : public Singleton<NetworkManager>
{
public:
    NetworkManager();
    virtual ~NetworkManager() final = default;

    virtual void Release() final;
    
};
