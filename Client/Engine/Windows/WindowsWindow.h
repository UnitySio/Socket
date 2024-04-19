#pragma once
#include "WindowDefinition.h"
#include "../framework.h"

class WindowsApplication;

class WindowsWindow
{
public:
    WindowsWindow();
    ~WindowsWindow();

    void Initialize(WindowsApplication* application, HINSTANCE instance_handle);

    inline HWND GetHWnd() const { return hWnd_; }

private:
    WindowsApplication* application_;
    WindowDefinition window_definition_;
    HWND hWnd_;
    
};
