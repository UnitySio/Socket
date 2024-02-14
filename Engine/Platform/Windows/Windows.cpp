#include "Windows.h"

#include "Window.h"
#include <crtdbg.h>

#define _CRTDBG_MAP_ALLOC

int APIENTRY wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nCmdShow
)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    Window* window = new Window();
    if (!window->InitWindow(hInstance, nCmdShow))
    {
        delete window;
        return 0;
    }

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

    delete window;
    return 0;
}