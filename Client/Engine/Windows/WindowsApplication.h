#pragma once
#include <vector>

#include "..\resource.h"
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
    static WindowsApplication* CreateWindowsApplication(const HINSTANCE instance_handle, const HICON icon_handle);
    
    WindowsApplication(const HINSTANCE instance_handle, const HICON icon_handle);
    ~WindowsApplication() = default;

    ATOM RegisterClass(const HINSTANCE instance_handle, const HICON icon_handle);

    std::shared_ptr<WindowsWindow> MakeWindow();
    
    void InitWindow(const std::shared_ptr<WindowsWindow>& kWindow, const std::shared_ptr<WindowsWindow>& kParentWindow);
    void AddMessageHandler(IWindowsMessageHandler& message_handler);
    void RemoveMessageHandler(IWindowsMessageHandler& message_handler);

private:
    friend LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    MathTypes::uint32 ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    std::shared_ptr<WindowsWindow> FindWindowByHWND(HWND hWnd) const;

    HINSTANCE instance_handle_;

    std::vector<std::shared_ptr<WindowsWindow>> windows_;
    std::vector<IWindowsMessageHandler*> message_handlers_;
    
};