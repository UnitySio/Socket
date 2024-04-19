#define _CRTDBG_MAP_ALLOC

#include "Client.h"
#include "Engine/WindowsApplication.h"

#include <crtdbg.h>

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

    WindowsApplication* application = new WindowsApplication(hInstance, nullptr);
    application->InitializeWindow();
    application->InitializeWindow();
    application->InitializeWindow();
    application->InitializeWindow();
    application->InitializeWindow();

#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

#ifdef _DEBUG
    _CrtDumpMemoryLeaks();
#endif

    delete application;
    return 0;
}