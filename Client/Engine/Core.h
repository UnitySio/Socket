#pragma once
#include "Windows/WindowsApplication.h"

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

    SHARED_PTR<GameEngine> game_engine_;

    HANDLE game_thread_handle_;

    bool is_game_running_;

    static double current_time_;
    static double last_time_;
    static double delta_time_;
    
    static MathTypes::uint32 resize_width_;
    static MathTypes::uint32 resize_height_;
    
};
