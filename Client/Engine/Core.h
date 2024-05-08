#pragma once
#include "Windows/WindowsApplication.h"

class Keyboard;
class Renderer;
class GameEngine;

class Core : public IWindowsMessageHandler
{
public:
    Core();
    ~Core();

    void Init(const HINSTANCE instance_handle);
    
    virtual bool ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result) override;

private:
    static DWORD WINAPI GameThread(LPVOID lpParam);
    
    SHARED_PTR<WindowsApplication> current_application_;
    WEAK_PTR<WindowsWindow> game_window_;

    SHARED_PTR<Renderer> renderer_;
    SHARED_PTR<GameEngine> game_engine_;
    SHARED_PTR<Keyboard> keyboard_;

    HANDLE game_thread_handle_;

    bool is_game_running_;

    static double current_time_;
    static double last_time_;
    static double delta_time_;
    
};
