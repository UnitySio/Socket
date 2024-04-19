#pragma once
#include "../framework.h"

class WindowsApplication;

class WindowsWindow
{
public:
    WindowsWindow();
    ~WindowsWindow() = default;

    void Initialize(WindowsApplication* application, HINSTANCE instance_handle);

private:
    WindowsApplication* application_;

    HWND hWnd_;
    
};
