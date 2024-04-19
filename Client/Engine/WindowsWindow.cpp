﻿#include "WindowsWindow.h"

#include "Math/MathTypes.h"

WindowsWindow::WindowsWindow() :
    application_(nullptr),
    hWnd_(nullptr)
{
}

void WindowsWindow::Initialize(WindowsApplication* const application, HINSTANCE instance_handle)
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
    MathTypes::uint32 window_width = 960;
    MathTypes::uint32 window_height = 540;

    window_x += border_rect.left;
    window_y += border_rect.top;
    window_width += border_rect.right - border_rect.left;
    window_height += border_rect.bottom - border_rect.top;

    hWnd_ = CreateWindowEx(
        window_ex_style,
        L"GEWindow",
        L"Game Engine",
        window_style,
        window_x, window_y,
        window_width, window_height,
        nullptr,
        nullptr,
        instance_handle,
        nullptr
        );

    if (!hWnd_) return;
    ShowWindow(hWnd_, SW_SHOW);
}
