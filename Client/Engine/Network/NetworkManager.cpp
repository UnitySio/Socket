#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
}

void NetworkManager::Release()
{
    Singleton<NetworkManager>::Release();
}
