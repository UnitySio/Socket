﻿#define _CRTDBG_MAP_ALLOC

#include "Client.h"
#include "Engine/Windows/WindowsApplication.h"

#include <crtdbg.h>
#include <iostream>

#include "GameEngine.h"
#include "Windows/WindowsWindow.h"

int APIENTRY wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nCmdShow
)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);
    
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    WindowsApplication* application = WindowsApplication::CreateWindowsApplication(hInstance, hIcon);

    // std::shared_ptr<WindowsWindow> main_window = WindowsWindow::Make();
    // application->InitWindow(main_window, nullptr);
    // main_window.reset();

    // 콘솔 로그 출력
    // OutputDebugString(L"Hello, World!");
    // std::cout << "Hello, World!" << std::endl;

    GameEngine* game_engine = new GameEngine();
    game_engine->Init(application);

    MSG msg = {};
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    delete game_engine;
    delete application;
    
#ifdef _DEBUG
    _CrtDumpMemoryLeaks();
#endif
    
    return 0;
}
