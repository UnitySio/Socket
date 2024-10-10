﻿#include "pch.h"
#define _CRTDBG_MAP_ALLOC

#include "Client.h"
#include "Core.h"

#include <crtdbg.h>
#include <iostream>

#include "Windows/WindowsWindow.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    
    HICON icon_handle = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    WindowsApplication* application = new WindowsApplication(hInstance, icon_handle);

    Core* core = new Core();
    core->Init(application);

    MSG msg = {};
    while (msg.message != WM_QUIT)
    {
        if (GetMessage(&msg, nullptr, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    SAFE_RELEASE(core);
    SAFE_RELEASE(application);
    
    return 0;
}
