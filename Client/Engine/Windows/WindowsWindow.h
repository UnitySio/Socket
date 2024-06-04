#pragma once

#include "../framework.h"
#include "Misc/EngineMacros.h"

struct WindowDefinition;
class WindowsApplication;

class WindowsWindow
{
public:
    WindowsWindow();
    ~WindowsWindow();

    static WCHAR window_class[];

    static SHARED_PTR<WindowsWindow> Make();

    void Init(WindowsApplication* const application, const SHARED_PTR<WindowDefinition>& kDefinition, HINSTANCE instance_handle, const SHARED_PTR<WindowsWindow>& kParentWindow);
    void SetWindowFocus();

    inline HWND GetHWnd() const { return hWnd_; }
    inline const WindowDefinition* GetDefinition() const { return definition_.get(); }

private:
    WindowsApplication* application_;
    HWND hWnd_;

    SHARED_PTR<WindowDefinition> definition_;
    
};