#include "Core.h"

#include "GameEngine.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "Math/Vector2.h"
#include "Windows/WindowsWindow.h"
#include "Windows/D3D/Renderer.h"
#include "Windows/D3D/Shape.h"
#include "Windows/D3D/ShapeBatch.h"

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
    current_application_ = std::shared_ptr<WindowsApplication>(WindowsApplication::CreateWindowsApplication(instance_handle, icon_handle));
    current_application_->AddMessageHandler(*this);

    // DirectX 11 렌더러 생성
    renderer_ = std::make_shared<Renderer>();
    renderer_->Init();

    g_renderer = renderer_.get();

    // 게임 윈도우 생성
    std::shared_ptr<WindowsWindow> new_window = current_application_->MakeWindow();
    current_application_->InitWindow(new_window, nullptr);

    // 렌더러에 뷰포트 생성
    renderer_->CreateViewport(new_window, {640, 480});

    // 뷰포트에 깊이 스텐실 버퍼 생성
    if (const auto viewport = renderer_->FindViewport(new_window.get()))
    {
        renderer_->CreateDepthStencilBuffer(*viewport);
    }

    shape_batch_ = std::make_shared<ShapeBatch>();
    shape_batch_->Init();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.Fonts->AddFontFromFileTTF(".\\Game_Data\\NanumBarunGothic.ttf", 16.f, nullptr, io.Fonts->GetGlyphRangesKorean());
    io.Fonts->AddFontFromFileTTF(".\\Game_Data\\Silver.ttf", 18.f, nullptr, io.Fonts->GetGlyphRangesKorean());
    io.FontDefault = io.Fonts->Fonts[1];
    
    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(new_window->GetHWnd());
    ImGui_ImplDX11_Init(g_d3d_device.Get(), g_d3d_device_context.Get());
    
    game_window_ = new_window;

    // 게임 스레드 생성
    game_thread_handle_ = CreateThread(nullptr, 0, GameThread, this, 0, nullptr);

    // 게임 엔진 생성
    game_engine_ = std::make_shared<GameEngine>();
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

                ImGui_ImplWin32_Shutdown();
                ImGui_ImplDX11_Shutdown();
                ImGui::DestroyContext();
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
        if (const auto window = core->game_window_.lock())
        {
            renderer->BeginRender(window);
            std::shared_ptr<Shape> shape = std::make_shared<Shape>();

            std::vector<DefaultVertex> vertices;
            vertices.push_back({{100.f, 100.f, 0.f}, {1.f, 1.f, 1.f, 1.f}});

            for (MathTypes::uint32 i = 0; i < 64; ++i)
            {
                const float theta = 2.f * MATH_PI * i / 64;
                const float x = 100.f + 50.f * cosf(theta);
                const float y = 100.f + 50.f * sinf(theta);
                vertices.push_back({{x, y, 0.f}, {1.f, 1.f, 1.f, 1.f}});
            }

            vertices.push_back(vertices[1]);

            std::vector<MathTypes::uint32> indices;
            for (MathTypes::uint32 i = 0; i < 64; ++i)
            {
                indices.push_back(0);
                indices.push_back(i + 1);
                indices.push_back(i + 2);
            }

            shape->SetVertices(vertices);
            shape->SetIndices(indices);

            static float x = 0.f;
            x += .01f;
            shape->SetPosition({320.f, 240.f});
            shape->SetRotation(x);
            
            core->shape_batch_->DrawShape(window, shape);
            shape.reset();

            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            // ...

            ImGui::Render();
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
            
            renderer->EndRender();
        }
        
        game_engine->Tick();
        if (!core->is_game_running_) break;
    }
    
    return 0;
}
