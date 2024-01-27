#include <iostream>
#include <thread>

#include "WinSock2.h"

#pragma comment(lib, "ws2_32.lib")

SOCKET listen_socket, client_socket;

void AcceptThread()
{
    while (true)
    {
        SOCKADDR_IN client_addr;
        int addr_len = sizeof(client_addr);
        client_socket = accept(listen_socket, reinterpret_cast<SOCKADDR*>(&client_addr), &addr_len);
    }
}

int main()
{
    WSAData wsa_data;
    WSAStartup(MAKEWORD(2, 2), &wsa_data);

    listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9000);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(listen_socket, reinterpret_cast<SOCKADDR*>(&server_addr), sizeof(server_addr));
    listen(listen_socket, SOMAXCONN);

    std::thread accept_thread(AcceptThread);
    accept_thread.join();

    WSACleanup();
    return 0;
}

