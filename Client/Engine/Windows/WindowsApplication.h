#pragma once
#include <vector>

#include "Singleton.h"
#include "../framework.h"
#include "Math/MathTypes.h"

struct WindowDefinition;
class WindowsWindow;

class IWindowsMessageHandler
{
public:
    virtual bool ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result) = 0;
    
};

class WindowsApplication
{
public:
    static WindowsApplication* CreateWindowsApplication(HINSTANCE instance_handle, HICON icon_handle);
    
    WindowsApplication(HINSTANCE instance_handle, HICON icon_handle);
    ~WindowsApplication() = default;

    ATOM RegisterClass(HINSTANCE instance_handle, HICON icon_handle);

    std::shared_ptr<WindowsWindow> MakeWindow();
    
    void InitializeWindow(const std::shared_ptr<WindowsWindow>& window, const std::shared_ptr<WindowsWindow>& parent_window);

private:
    friend LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    MathTypes::uint32 ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    std::shared_ptr<WindowsWindow> FindWindowByHWND(HWND hWnd) const;

    void AddMessageHandler(IWindowsMessageHandler& message_handler);
    void RemoveMessageHandler(IWindowsMessageHandler& message_handler);

    HINSTANCE instance_handle_;

    std::vector<std::shared_ptr<WindowsWindow>> windows_;
    std::vector<IWindowsMessageHandler*> message_handlers_;
    
};
