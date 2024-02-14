#include "Window.h"


HWND Window::hWnd_ = nullptr;
RECT Window::window_area_;

Window::Window() : resolution_()
{
}

bool Window::InitWindow(HINSTANCE hInstance, int nCmdShow)
{
    MyRegisterClass(hInstance);
    if (!InitInstance(hInstance, nCmdShow)) return false;

    return true;
}

ATOM Window::MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;
    ZeroMemory(&wcex, sizeof(WNDCLASSEX));

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
    wcex.lpszClassName = L"Engine";

    return RegisterClassEx(&wcex);
}

BOOL Window::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    const int screen_width = GetSystemMetrics(SM_CXSCREEN);
    const int screen_height = GetSystemMetrics(SM_CYSCREEN);
    
    resolution_ = {1366, 768};
    window_area_ = {0, 0, resolution_.x, resolution_.y};
    AdjustWindowRect(&window_area_, WS_OVERLAPPEDWINDOW, FALSE);

    hWnd_ = CreateWindowEx(
        0,
        L"Engine",
        L"Engine",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX,
        (screen_width - (window_area_.right - window_area_.left)) / 2,
        (screen_height - (window_area_.bottom - window_area_.top)) / 2,
        window_area_.right - window_area_.left,
        window_area_.bottom - window_area_.top,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );
    
    if (!hWnd_) return FALSE;
    ShowWindow(hWnd_, nCmdShow);

    return TRUE;
}

LRESULT Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_GETMINMAXINFO)
    {
        reinterpret_cast<MINMAXINFO*>(lParam)->ptMinTrackSize.x = window_area_.right - window_area_.left;
        reinterpret_cast<MINMAXINFO*>(lParam)->ptMinTrackSize.y = window_area_.bottom - window_area_.top;
        reinterpret_cast<MINMAXINFO*>(lParam)->ptMaxTrackSize.x = window_area_.right - window_area_.left;
        reinterpret_cast<MINMAXINFO*>(lParam)->ptMaxTrackSize.y = window_area_.bottom - window_area_.top;

        return 0;
    }

    if (message == WM_DESTROY)
    {
        PostQuitMessage(0);
        return 0;
    }
    
    return DefWindowProc(hWnd, message, wParam, lParam);
}
