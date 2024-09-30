#pragma once

#pragma once

#define WIN32_LEAN_AND_MEAN

#include <mutex>
#include <atomic>
using BYTE = unsigned char;
#include "CoreMacro.h"
#include "CoreTLS.h"
#include "CoreGlobal.h"
#include <array>
#include <vector>
#include <queue>
#include <set>

#include <cstdlib>
#include <ctime>

#include <windows.h>
#include <iostream>
using namespace std;

#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

#include "Lock.h"
#include "Session.h"
#include "ThreadManager.h"
#include "Service.h"
#include "JobQueue.h"