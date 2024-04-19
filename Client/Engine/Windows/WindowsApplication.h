#pragma once
#include <vector>

#include "Singleton.h"
#include "../framework.h"
#include "Math/MathTypes.h"

struct WindowDefinition;
class WindowsWindow;

class WindowsApplication
{
public:
    static WindowsApplication* CreateWindowsApplication(HINSTANCE instance_handle, HICON icon_handle);
    
    WindowsApplication(HINSTANCE instance_handle, HICON icon_handle);
    ~WindowsApplication();

    ATOM RegisterClass(HINSTANCE instance_handle, HICON icon_handle);

    void InitializeWindow();

private:
    friend LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    MathTypes::uint32 ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    std::shared_ptr<WindowsWindow> FindWindowByHWND(HWND hWnd) const;

    HINSTANCE instance_handle_;

    std::vector<std::shared_ptr<WindowsWindow>> windows_;
    
};
