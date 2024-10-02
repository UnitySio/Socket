#pragma once
#include "Windows/WindowsApplication.h"

class Renderer;
class GameEngine;

class Core : public IWindowsMessageHandler
{
public:
    Core();
    ~Core() = default;

    void Init(const HINSTANCE kInstanceHandle);
    
    virtual bool ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result) override;

private:
    void MainThread();
    void Start();
    void Stop();
    
    std::shared_ptr<WindowsApplication> current_application_;
    std::weak_ptr<WindowsWindow> game_window_;

    std::shared_ptr<GameEngine> game_engine_;
    
    std::atomic<bool> is_running_;
    std::thread main_thread_;
    std::mutex mutex_;

    double current_time_;
    double last_time_;
    double delta_time_;
    
};
