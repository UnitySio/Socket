#include "pch.h"
#define _CRTDBG_MAP_ALLOC

#include "Client.h"
#include "Core.h"
#include "Misc/EngineMacros.h"

#include <crtdbg.h>
#include <iostream>

#include "Windows/WindowsWindow.h"

START
{
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    Core* core = new Core();
    core->Init(hInstance);

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
    
    return 0;
}
