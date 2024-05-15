﻿#include "WindowsApplication.h"

#include "WindowsWindow.h"
#include "combaseapi.h"

WindowsApplication::WindowsApplication(const HINSTANCE instance_handle, const HICON icon_handle) :
    instance_handle_(instance_handle),
    windows_()
{
    RegisterClass(instance_handle, icon_handle);
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);
}

WindowsApplication::~WindowsApplication()
{
    CoUninitialize();
}

ATOM WindowsApplication::RegisterClass(const HINSTANCE instance_handle, const HICON icon_handle)
{
    WNDCLASSEX wcex;
    ZeroMemory(&wcex, sizeof(WNDCLASSEX));

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = StaticWndProc;
    wcex.hInstance = instance_handle;
    wcex.hIcon = icon_handle;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
    wcex.lpszClassName = WindowsWindow::window_class;

    return RegisterClassEx(&wcex);
}

SHARED_PTR<WindowsWindow> WindowsApplication::MakeWindow()
{
    return WindowsWindow::Make();
}

void WindowsApplication::InitWindow(const SHARED_PTR<WindowsWindow>& kWindow, const SHARED_PTR<WindowDefinition>& kDefinition, const SHARED_PTR<WindowsWindow>& kParentWindow)
{
    windows_.push_back(kWindow);
    kWindow->Init(this, kDefinition, instance_handle_, kParentWindow);
}

void WindowsApplication::AddMessageHandler(IWindowsMessageHandler& message_handler)
{
    for (const auto& handler : message_handlers_)
    {
        if (handler == &message_handler) return;
    }
    
    message_handlers_.push_back(&message_handler);
}

void WindowsApplication::RemoveMessageHandler(IWindowsMessageHandler& message_handler)
{
    std::erase(message_handlers_, &message_handler);
}

LRESULT WindowsApplication::StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    WindowsApplication* application = nullptr;

    if (message == WM_NCCREATE)
    {
        LPCREATESTRUCT create_struct = reinterpret_cast<LPCREATESTRUCT>(lParam);
        application = static_cast<WindowsApplication*>(create_struct->lpCreateParams);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(application));
    }
    else application = reinterpret_cast<WindowsApplication*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

    if (application) return application->ProcessMessage(hWnd, message, wParam, lParam);
    return DefWindowProc(hWnd, message, wParam, lParam);
}

MathTypes::uint32 WindowsApplication::ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    SHARED_PTR<WindowsWindow> window = FindWindowByHWND(hWnd);
    
    if (window)
    {
        bool is_external_handled = false;
        MathTypes::uint32 external_handler_result = 0;
        
        for (const auto& handler : message_handlers_)
        {
            MathTypes::uint32 handler_result = 0;
            if (handler->ProcessMessage(hWnd, message, wParam, lParam, handler_result))
            {
                if (!is_external_handled)
                {
                    is_external_handled = true;
                    external_handler_result = handler_result;
                }
            }
        }
        
        if (message == WM_DESTROY)
        {
            std::erase(windows_, window);

            if (windows_.empty()) PostQuitMessage(0);
            return 0;
        }

        if (is_external_handled) return external_handler_result;
    }
    
    return DefWindowProc(hWnd, message, wParam, lParam);
}

SHARED_PTR<WindowsWindow> WindowsApplication::FindWindowByHWND(HWND hWnd) const
{
    for (const auto& window : windows_)
    {
        if (window->GetHWnd() == hWnd) return window;
    }
    
    return nullptr;
}