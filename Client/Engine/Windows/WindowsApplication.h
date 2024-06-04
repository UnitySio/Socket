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
    WindowsApplication(const HINSTANCE instance_handle, const HICON icon_handle);
    ~WindowsApplication();

    ATOM RegisterClass(const HINSTANCE instance_handle, const HICON icon_handle);

    SHARED_PTR<WindowsWindow> MakeWindow();
    
    void InitWindow(const SHARED_PTR<WindowsWindow>& kWindow, const SHARED_PTR<WindowDefinition>& kDefinition, const SHARED_PTR<WindowsWindow>& kParentWindow);
    void AddMessageHandler(IWindowsMessageHandler& message_handler);
    void RemoveMessageHandler(IWindowsMessageHandler& message_handler);

    const std::vector<SHARED_PTR<WindowsWindow>>& GetWindows() const { return windows_; }

private:
    static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    MathTypes::uint32 ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    SHARED_PTR<WindowsWindow> FindWindowByHWND(HWND hWnd) const;

    HINSTANCE instance_handle_;

    std::vector<SHARED_PTR<WindowsWindow>> windows_;
    std::vector<IWindowsMessageHandler*> message_handlers_;
    
};