#include "Scene.h"

#include "imgui/imgui.h"

#define PORT 9000
#define BUFFER_SIZE 1024

Scene::Scene()
{
    WSAData wsa_data;
    WSAStartup(MAKEWORD(2, 2), &wsa_data);

    server_socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN server_addr = {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(server_socket_, reinterpret_cast<SOCKADDR*>(&server_addr), sizeof(server_addr));
    listen(server_socket_, SOMAXCONN);

    AddLog(u8"클라이언트 연결 대기 중...");
}

void Scene::Release()
{
    closesocket(server_socket_);
    WSACleanup();
    
    Singleton<Scene>::Release();
}

void Scene::Tick(float delta_time)
{
    // SOCKADDR_IN client_addr = {};
    // int client_addr_size = sizeof(client_addr);
    // SOCKET client_socket = accept(server_socket_, reinterpret_cast<SOCKADDR*>(&client_addr), &client_addr_size);
    //
    // if (client_socket != INVALID_SOCKET)
    // {
    //     AddLog(u8"클라이언트 연결 성공!");
    //
    //     char buffer[BUFFER_SIZE] = {};
    //     recv(client_socket, buffer, BUFFER_SIZE, 0);
    //
    //     AddLog(u8"클라이언트 메시지: %s", buffer);
    //
    //     closesocket(client_socket);
    // }
}

void Scene::Render()
{
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
    if (ImGui::Begin(u8"콘솔"))
    {

        if (ImGui::BeginChild("Logs"))
        {
            for (auto& log : logs_)
            {
                ImGui::Text(log.c_str());
            }
        }
        ImGui::EndChild();
    }

    ImGui::End();
}

void Scene::AddLog(std::string format, ...)
{
    va_list args;
    va_start(args, format);

    char buffer[1024];
    vsprintf_s(buffer, format.c_str(), args);

    logs_.push_back(buffer);
    va_end(args);
}
