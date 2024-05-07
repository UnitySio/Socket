#include "WindowsApplication.h"

#include "WindowsWindow.h"
#include "DirectXTK/Audio.h"
#include "Input/Keyboard.h"

WindowsApplication* windows_application = nullptr;

WindowsApplication* WindowsApplication::CreateWindowsApplication(const HINSTANCE instance_handle, const HICON icon_handle)
{
    windows_application = new WindowsApplication(instance_handle, icon_handle);
    return windows_application;
}

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

std::shared_ptr<WindowsWindow> WindowsApplication::MakeWindow()
{
    return WindowsWindow::Make();
}

void WindowsApplication::InitWindow(const std::shared_ptr<WindowsWindow>& kWindow, const std::shared_ptr<WindowsWindow>& kParentWindow)
{
    windows_.push_back(kWindow);
    kWindow->Init(this, instance_handle_, kParentWindow);
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
    std::shared_ptr<WindowsWindow> window = FindWindowByHWND(hWnd);
    
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

        if (message == WM_SYSKEYUP ||
            message == WM_SYSKEYDOWN ||
            message == WM_KEYUP ||
            message == WM_KEYDOWN)
        {
            bool was_down = (lParam & (1 << 30)) != 0;
            bool is_down = (lParam & (1 << 31)) == 0;
            
            Keyboard::Process(wParam, was_down, is_down);
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

std::shared_ptr<WindowsWindow> WindowsApplication::FindWindowByHWND(HWND hWnd) const
{
    for (const auto& window : windows_)
    {
        if (window->GetHWnd() == hWnd) return window;
    }
    
    return nullptr;
}