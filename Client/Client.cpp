#include "pch.h"
#define _CRTDBG_MAP_ALLOC

#include "Client.h"
#include "Core.h"
#include "Misc/EngineMacros.h"

#include <crtdbg.h>
#include <iostream>

#include "Steam/SteamManager.h"
#include "Windows/WindowsWindow.h"

START
{
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    // SteamManager* steam = SteamManager::Get();
    // int result = steam->Init();
    // if (result == 1)
    // {
    //     MessageBox(nullptr, L"Restarting app.", L"Error", MB_OK);
    //     return 1;
    // }
    //
    // if (result == -1)
    // {
    //     MessageBox(nullptr, L"Failed to initialize Steam API.", L"Error", MB_OK);
    //     return -1;
    // }

    Core* core = new Core();
    core->Init(hInstance);

    MSG msg = {};
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    SAFE_RELEASE(core);

    // steam->Shutdown();
    
    return 0;
}
