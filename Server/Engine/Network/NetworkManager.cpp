#include "NetworkManager.h"

#include "../Scene.h"

#define PORT 9000

NetworkManager::NetworkManager()
{
}

void NetworkManager::Release()
{
    closesocket(server_socket_);
    WSACleanup();
    
    Singleton<NetworkManager>::Release();
}

bool NetworkManager::InitServer()
{
    std::shared_ptr<Scene> scene = Scene::GetInstance();

    WSAData wsa_data;
    int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (result != 0)
    {
        scene->AddLog(u8"[에러] WinSock 초기화 실패: %s", WSAGetLastError());
        return false;
    }

    server_socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_ == INVALID_SOCKET)
    {
        scene->AddLog(u8"[에러] 소켓 생성 실패: %s", WSAGetLastError());
        return false;
    }

    SOCKADDR_IN server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(server_socket_, reinterpret_cast<SOCKADDR*>(&server_address), sizeof(server_address));
    listen(server_socket_, SOMAXCONN);
    
    return true;
}

void NetworkManager::StartServer()
{
    std::shared_ptr<Scene> scene = Scene::GetInstance();
    scene->AddLog(u8"클라이언트의 접속을 기다리는 중...");
    
    accept_thread_handle_ = CreateThread(nullptr, 0, AcceptThread, nullptr, 0, nullptr);
}

DWORD NetworkManager::AcceptThread(LPVOID lpParam)
{
    std::shared_ptr<Scene> scene = Scene::GetInstance();

    while (true)
    {
        SOCKADDR_IN client_address;
        int client_address_size = sizeof(client_address);
        SOCKET client_socket = accept(NetworkManager::GetInstance()->server_socket_,
                                      reinterpret_cast<SOCKADDR*>(&client_address), &client_address_size);

        if (client_socket != INVALID_SOCKET)
        {
            scene->AddLog(u8"클라리언트 접속 확인");
        }
    }
    
    return 0;
}
