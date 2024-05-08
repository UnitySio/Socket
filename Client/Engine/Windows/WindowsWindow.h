#pragma once

#include "../framework.h"
#include "Misc/EngineMacros.h"

class WindowsApplication;

class WindowsWindow
{
public:
    WindowsWindow();
    ~WindowsWindow();

    static WCHAR window_class[];

    static SHARED_PTR<WindowsWindow> Make();

    void Init(WindowsApplication* const application, HINSTANCE instance_handle, const SHARED_PTR<WindowsWindow>& kParentWindow);
    void SetWindowFocus();

    inline HWND GetHWnd() const { return hWnd_; }

private:
    WindowsApplication* application_;
    HWND hWnd_;
    
};