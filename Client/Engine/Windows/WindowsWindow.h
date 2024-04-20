#pragma once
#include <memory>

#include "WindowDefinition.h"
#include "../framework.h"

class WindowsApplication;

class WindowsWindow
{
public:
    WindowsWindow();
    ~WindowsWindow();

    static std::shared_ptr<WindowsWindow> Make();

    void Initialize(WindowsApplication* application, HINSTANCE instance_handle, const std::shared_ptr<WindowsWindow>& parent_window);

    inline HWND GetHWnd() const { return hWnd_; }

private:
    WindowsApplication* application_;
    WindowDefinition window_definition_;
    HWND hWnd_;
    
};
