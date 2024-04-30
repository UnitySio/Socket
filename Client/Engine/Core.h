#pragma once
#include "DirectXTK/SpriteBatch.h"
#include "DirectXTK/SpriteFont.h"
#include "Windows/WindowsApplication.h"

class ShapeBatch;
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
    
    std::shared_ptr<WindowsApplication> current_application_;
    std::weak_ptr<WindowsWindow> game_window_;

    std::shared_ptr<Renderer> renderer_;
    std::shared_ptr<ShapeBatch> shape_batch_;
    std::shared_ptr<GameEngine> game_engine_;

    HANDLE game_thread_handle_;

    bool is_game_running_;

    std::unique_ptr<DirectX::DX11::SpriteBatch> sprite_batch_;
    std::unique_ptr<DirectX::DX11::SpriteFont> sprite_font_;
    
};
