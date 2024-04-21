﻿#pragma once
#include "Windows/WindowsApplication.h"

class Core : public IWindowsMessageHandler
{
public:
    static Core* Create();
    
    Core();
    ~Core();

    void Init(const HINSTANCE instance_handle);
    
    virtual bool ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result) override;

private:
    static DWORD WINAPI GameThread(LPVOID lpParam);
    
    std::shared_ptr<WindowsApplication> current_application_;
    std::weak_ptr<WindowsWindow> game_window_;

    HANDLE game_thread_handle_;

    bool is_game_running_;
    
};
