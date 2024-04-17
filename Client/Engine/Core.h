﻿#pragma once
#include "Singleton.h"
#include "../framework.h"

class Core : public Singleton<Core>
{
public:
    Core();
    virtual ~Core() override = default;

    ATOM MyRegisterClass(HINSTANCE hInstance);
    BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

    bool InitWindow(HINSTANCE hInstance, int nCmdShow);

    inline POINT GetResolution() const { return resolution_; }
    inline HWND GetWindowHandle() const { return hWnd_; }
    inline HWND GetFocusHandle() const { return focus_; }

private:
    static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    static DWORD WINAPI LogicThread(LPVOID lpParam);
    
    void MainLogic();
    void Tick(float delta_time);
    void Render(float alpha);

    POINT resolution_;
    RECT window_area_;

    HWND hWnd_;
    HWND focus_;

    HANDLE logic_handle_;

    bool is_running_;

    float alpha_;
    
};
