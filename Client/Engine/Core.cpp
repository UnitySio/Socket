#include "Core.h"

#include "GameEngine.h"
#include "Math/Vector2.h"
#include "Time/Time.h"
#include "Windows/WindowDefinition.h"
#include "Windows/WindowsWindow.h"
#include "Windows/D3D/Renderer.h"

SHARED_PTR<WindowsWindow> g_game_window;

double Core::current_time_ = 0.;
double Core::last_time_ = 0.;
double Core::delta_time_ = 0.;

Core::Core() :
    current_application_(nullptr),
    game_window_(),
    renderer_(nullptr),
    game_thread_handle_(nullptr),
    is_game_running_(false)
{
}

Core::~Core()
{
}

void Core::Init(const HINSTANCE instance_handle)
{
    // 윈도우 애플리케이션을 생성하고 메시지 핸들러로 등록
    HICON icon_handle = LoadIcon(instance_handle, MAKEINTRESOURCE(IDI_ICON1));
    current_application_ = SHARED_PTR<WindowsApplication>(WindowsApplication::CreateWindowsApplication(instance_handle, icon_handle));
    current_application_->AddMessageHandler(*this);

    // DirectX 11 렌더러 생성
    renderer_ = MAKE_SHARED<Renderer>();
    renderer_->Init();

    g_renderer = renderer_.get();

    // 게임 윈도우 정의 생성
    SHARED_PTR<WindowDefinition> definition = MAKE_SHARED<WindowDefinition>();
    definition->title = L"Fusion2D";
    definition->screen_x = 100;
    definition->screen_y = 100;
    definition->width = 1024;
    definition->height = 768;

    // 게임 윈도우 생성
    SHARED_PTR<WindowsWindow> new_window = current_application_->MakeWindow();
    current_application_->InitWindow(new_window, definition, nullptr);

    // 렌더러에 뷰포트 생성
    renderer_->CreateViewport(new_window, {definition->width, definition->height});

    // 뷰포트에 깊이 스텐실 버퍼 생성
    if (const auto viewport = renderer_->FindViewport(new_window.get()))
    {
        renderer_->CreateDepthStencilBuffer(*viewport);
    }
    
    game_window_ = new_window;
    
    // 게임 엔진 생성
    game_engine_ = MAKE_SHARED<GameEngine>();
    game_engine_->Init(new_window);

    current_time_ = Time::Init();

    // 게임 스레드 생성
    game_thread_handle_ = CreateThread(nullptr, 0, GameThread, this, 0, nullptr);
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool Core::ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam)) return true;
    
    if (message == WM_DESTROY)
    {
        if (const auto window = game_window_.lock())
        {
            if (window->GetHWnd() == hWnd)
            {
                is_game_running_ = false;
                
                // 게임 스레드가 종료될 때까지 대기
                WaitForSingleObject(game_thread_handle_, INFINITE);

                game_engine_->OnQuit();
            }
        }
    }
    
    return false;
}

DWORD Core::GameThread(LPVOID lpParam)
{
    Core* core = static_cast<Core*>(lpParam);
    if (!core) return 0;

    GameEngine* game_engine = core->game_engine_.get();
    core->is_game_running_ = true;

    Renderer* renderer = core->renderer_.get();
    
    while (true)
    {
#pragma region DeltaTime
        last_time_ = current_time_;
        current_time_ = Time::Seconds();
        delta_time_ = current_time_ - last_time_;
#pragma endregion
        
        if (const auto& window = core->game_window_.lock())
        {
            renderer->BeginRender(window);
            game_engine->GameLoop(delta_time_);
            renderer->EndRender();
        }
        
        if (!core->is_game_running_) break;
    }
    
    return 0;
}
