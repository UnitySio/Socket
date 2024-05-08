#include "WindowsWindow.h"

#include "Math/MathTypes.h"

WindowsWindow::WindowsWindow() :
    application_(nullptr),
    hWnd_(nullptr)
{
}

WindowsWindow::~WindowsWindow()
{
}

WCHAR WindowsWindow::window_class[] = L"GEWindow";

SharedPtr<WindowsWindow> WindowsWindow::Make()
{
    return MakeShared<WindowsWindow>();
}

void WindowsWindow::Init(WindowsApplication* const application, HINSTANCE instance_handle, const SharedPtr<WindowsWindow>& kParentWindow)
{
    application_ = application;

    MathTypes::uint32 window_ex_style = 0;
    MathTypes::uint32 window_style = 0;
    
    window_style |= WS_OVERLAPPED;
    window_style |= WS_CAPTION;
    window_style |= WS_SYSMENU;
    window_style |= WS_THICKFRAME;
    window_style |= WS_MINIMIZEBOX;

    RECT border_rect = {0, 0, 0, 0};
    AdjustWindowRectEx(&border_rect, window_style, false, window_ex_style);

    MathTypes::uint32 window_x = 100;
    MathTypes::uint32 window_y = 100;
    MathTypes::uint32 window_width = 640;
    MathTypes::uint32 window_height = 480;

    window_x += border_rect.left;
    window_y += border_rect.top;
    window_width += border_rect.right - border_rect.left;
    window_height += border_rect.bottom - border_rect.top;

    hWnd_ = CreateWindowEx(
        window_ex_style,
        window_class,
        L"Game Engine",
        window_style,
        window_x, window_y,
        window_width, window_height,
        kParentWindow ? kParentWindow->GetHWnd() : nullptr,
        nullptr,
        instance_handle,
        nullptr
        );

    if (!hWnd_) return;
    ShowWindow(hWnd_, SW_SHOW);
}

void WindowsWindow::SetWindowFocus()
{
    if (GetFocus() != hWnd_) SetFocus(hWnd_);
}