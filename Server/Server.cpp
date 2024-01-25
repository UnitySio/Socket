#include <iostream>
#include "WinSock2.h"

#pragma comment(lib, "ws2_32.lib")

int main()
{
    WSAData wsa_data_;
    WSAStartup(MAKEWORD(2, 2), &wsa_data_);

    WSACleanup();
    return 0;
}

