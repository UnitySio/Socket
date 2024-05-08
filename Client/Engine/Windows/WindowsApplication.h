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
    ~WindowsApplication();

    ATOM RegisterClass(const HINSTANCE instance_handle, const HICON icon_handle);

    SharedPtr<WindowsWindow> MakeWindow();
    
    void InitWindow(const SharedPtr<WindowsWindow>& kWindow, const SharedPtr<WindowsWindow>& kParentWindow);
    void AddMessageHandler(IWindowsMessageHandler& message_handler);
    void RemoveMessageHandler(IWindowsMessageHandler& message_handler);

    const std::vector<SharedPtr<WindowsWindow>>& GetWindows() const { return windows_; }

private:
    friend LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    MathTypes::uint32 ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    SharedPtr<WindowsWindow> FindWindowByHWND(HWND hWnd) const;

    HINSTANCE instance_handle_;

    std::vector<SharedPtr<WindowsWindow>> windows_;
    std::vector<IWindowsMessageHandler*> message_handlers_;
    
};