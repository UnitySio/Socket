#pragma once
#include <vector>

#include "Singleton.h"
#include "../framework.h"

class WindowsWindow;

class WindowsApplication
{
public:
    static WindowsApplication* CreateWindowsApplication(HINSTANCE instance_handle, HICON icon_handle);
    
    WindowsApplication(HINSTANCE instance_handle, HICON icon_handle);
    ~WindowsApplication() = default;

    ATOM RegisterClass(HINSTANCE instance_handle, HICON icon_handle);

    bool InitWindow();

    void InitializeWindow();

    inline POINT GetResolution() const { return resolution_; }
    inline HWND GetWindowHandle() const { return hWnd_; }
    inline HWND GetFocusHandle() const { return focus_; }

private:
    friend LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    static DWORD WINAPI LogicThread(LPVOID lpParam);
    
    void MainLogic();
    void Tick(float delta_time);
    void Render(float alpha);

    HINSTANCE instance_handle_;

    std::vector<std::shared_ptr<WindowsWindow>> windows_;

    POINT resolution_;
    RECT window_area_;

    HWND hWnd_;
    HWND focus_;

    HANDLE logic_handle_;

    bool is_running_;

    float alpha_;
    
};
