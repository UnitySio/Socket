#pragma once
#include "framework.h"
#include "Misc/Singleton.h"

class Window : public Singleton<Window>
{
public:
    Window();
    ~Window() = default;
    
    bool InitWindow(HINSTANCE hInstance, int nCmdShow);

    static HWND GetWindowHandle() { return hWnd_; }

private:
    ATOM MyRegisterClass(HINSTANCE hInstance);
    
    BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
    
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    
    static HWND hWnd_;
    
    static RECT window_area_;
    
    POINT resolution_;
    
};
