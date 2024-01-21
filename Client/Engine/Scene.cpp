#include "Scene.h"

#include "imgui/imgui.h"

#define PORT 9000
#define SERVER_IP "127.0.0.1"

Scene::Scene()
{
}

void Scene::Tick(float delta_time)
{
}

void Scene::Render()
{
    if (ImGui::Button(u8"서버 연결"))
    {
        WSAData wsa_data;
        WSAStartup(MAKEWORD(2, 2), &wsa_data);

        SOCKET client_socket = socket(AF_INET, SOCK_STREAM, 0);

        SOCKADDR_IN client_address;
        client_address.sin_family = AF_INET;
        client_address.sin_port = htons(PORT);
        client_address.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);

        connect(client_socket, reinterpret_cast<SOCKADDR*>(&client_address), sizeof(client_address));
    }
}