#pragma once
#include "Windows/WindowsApplication.h"

class GameEngine : public IWindowsMessageHandler
{
public:
    GameEngine();

    void Init(WindowsApplication* application);
    
    bool ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result) override;

private:
    static DWORD WINAPI GameThread(LPVOID lpParam);
    
    std::shared_ptr<WindowsWindow> game_window_;

    HANDLE game_thread_;
    
};
