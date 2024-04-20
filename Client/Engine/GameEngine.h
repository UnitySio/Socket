#pragma once
#include "Windows/WindowsApplication.h"

class GameEngine : public IWindowsMessageHandler
{
public:
    bool ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result) override;
    
};
