#include "WindowsApplication.h"

#include "WindowsWindow.h"

WindowsApplication* windows_application = nullptr;

WindowsApplication* WindowsApplication::CreateWindowsApplication(HINSTANCE instance_handle, HICON icon_handle)
{
    windows_application = new WindowsApplication(instance_handle, icon_handle);
    return windows_application;
}

WindowsApplication::WindowsApplication(HINSTANCE instance_handle, HICON icon_handle) :
    instance_handle_(instance_handle),
    windows_()
{
    RegisterClass(instance_handle, icon_handle);
}

ATOM WindowsApplication::RegisterClass(HINSTANCE instance_handle, HICON icon_handle)
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
    wcex.lpszClassName = L"GEWindow";

    return RegisterClassEx(&wcex);
}

std::shared_ptr<WindowsWindow> WindowsApplication::MakeWindow()
{
    return WindowsWindow::Make();
}

void WindowsApplication::InitializeWindow(const std::shared_ptr<WindowsWindow>& window, const std::shared_ptr<WindowsWindow>& parent_window)
{
    windows_.push_back(window);
    window->Initialize(this, instance_handle_, parent_window);
}

LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return windows_application->ProcessMessage(hWnd, message, wParam, lParam);
}

LRESULT WindowsApplication::StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return WndProc(hWnd, message, wParam, lParam);
}
MathTypes::uint32 WindowsApplication::ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    const std::shared_ptr<WindowsWindow> window = FindWindowByHWND(hWnd);
    if (window)
    {
        for (const auto& handler : message_handlers_)
        {
            MathTypes::uint32 handler_result = 0;
            if (handler->ProcessMessage(hWnd, message, wParam, lParam, handler_result))
            {
            }
        }
        
        if (message == WM_DESTROY)
        {
            std::erase(windows_, window);

            if (windows_.empty()) PostQuitMessage(0);
            return 0;
        }
    }
    
    return DefWindowProc(hWnd, message, wParam, lParam);
}

std::shared_ptr<WindowsWindow> WindowsApplication::FindWindowByHWND(HWND hWnd) const
{
    for (const auto& window : windows_)
    {
        if (window->GetHWnd() == hWnd) return window;
    }
    
    return nullptr;
}

void WindowsApplication::AddMessageHandler(IWindowsMessageHandler& message_handler)
{
    for (const auto& handler : message_handlers_)
    {
        if (handler == &message_handler) return;
    }
    
    windows_application->message_handlers_.push_back(&message_handler);
}

void WindowsApplication::RemoveMessageHandler(IWindowsMessageHandler& message_handler)
{
    std::erase(windows_application->message_handlers_, &message_handler);
}
