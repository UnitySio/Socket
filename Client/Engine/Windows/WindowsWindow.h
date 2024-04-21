﻿#pragma once
#include <memory>

#include "../framework.h"

class WindowsApplication;

class WindowsWindow
{
public:
    WindowsWindow();
    ~WindowsWindow();

    static WCHAR window_class[];

    static std::shared_ptr<WindowsWindow> Make();

    void Init(WindowsApplication* application, HINSTANCE instance_handle, const std::shared_ptr<WindowsWindow>& parent_window);
    void SetWindowFocus();

    inline HWND GetHWnd() const { return hWnd_; }

private:
    WindowsApplication* application_;
    HWND hWnd_;
    
};
