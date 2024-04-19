#define _CRTDBG_MAP_ALLOC

#include "Client.h"
#include "Engine/Windows/WindowsApplication.h"

#include <crtdbg.h>

#include "Windows/WindowsWindow.h"

HANDLE engine_thread;
DWORD WINAPI EngineThread(LPVOID lpParam);

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

    WindowsApplication* application = WindowsApplication::CreateWindowsApplication(hInstance, nullptr);

    std::shared_ptr<WindowsWindow> window = std::make_shared<WindowsWindow>();
    application->InitializeWindow(window, nullptr);

    engine_thread = CreateThread(nullptr, 0, EngineThread, nullptr, 0, nullptr);

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    WaitForSingleObject(engine_thread, INFINITE);

    delete application;
    
#ifdef _DEBUG
    _CrtDumpMemoryLeaks();
#endif
    
    return 0;
}

DWORD EngineThread(LPVOID lpParam)
{
    return 0;
}
