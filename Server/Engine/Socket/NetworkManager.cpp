#include "NetworkManager.h"

#include "../Scene.h"

NetworkManager::NetworkManager()
{
}

void NetworkManager::Release()
{
    Singleton<NetworkManager>::Release();
}

bool NetworkManager::Init()
{
    std::shared_ptr<Scene> scene = Scene::GetInstance();

    WSAData wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
    {
        scene->AddLog(u8"[에러] WSAStartup() 실패");
        return false;
    }
    
    return true;
}
