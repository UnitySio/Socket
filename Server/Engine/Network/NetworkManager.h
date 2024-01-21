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
    
    bool InitServer();

    void StartServer();

private:
    static DWORD WINAPI AcceptThread(LPVOID lpParam);
    
    SOCKET server_socket_;

    HANDLE accept_thread_handle_;
    
};
