#pragma once
#include "framework.h"

class Window
{
public:
    Window();
    ~Window() = default;

    ATOM RegisterWindowClass(HINSTANCE hInstance);
    
    BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
    BOOL InitWindow(HINSTANCE hInstance, int nCmdShow);

    static HWND GetWindowHandle() { return hWnd_; }

private:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    
    static HWND hWnd_;
    
    static RECT window_area_;
    
    POINT resolution_;
    
};
