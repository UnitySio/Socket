#include "Core.h"

#include <functional>
#include <iostream>

#include "EventManager.h"
#include "Vector.h"
#include "Graphics/Graphics.h"
#include "Time/Time.h"
#include "Level/World.h"
#include "Input/InputManager.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

Core::Core() :
    class_name_(L"GAME"),
    resolution_(),
    window_area_(),
    hWnd_(nullptr),
    focus_(nullptr),
    logic_handle_(nullptr),
    is_running_(false)
{
}

ATOM Core::MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;
    ZeroMemory(&wcex, sizeof(WNDCLASSEX));

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = StaticWndProc;
    wcex.hInstance = hInstance;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
    wcex.lpszClassName = class_name_.c_str();

    return RegisterClassEx(&wcex);
}

BOOL Core::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    const int screen_width = GetSystemMetrics(SM_CXSCREEN);
    const int screen_height = GetSystemMetrics(SM_CYSCREEN);

    resolution_ = {1366, 768};
    window_area_ = {0, 0, resolution_.x, resolution_.y};
    AdjustWindowRect(&window_area_, WS_OVERLAPPEDWINDOW, FALSE);

    hWnd_ = CreateWindowEx(
        0,
        class_name_.c_str(),
        L"Game",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX,
        (screen_width - (window_area_.right - window_area_.left)) / 2,
        (screen_height - (window_area_.bottom - window_area_.top)) / 2,
        window_area_.right - window_area_.left,
        window_area_.bottom - window_area_.top,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    if (!hWnd_) return FALSE;
    ShowWindow(hWnd_, nCmdShow);

    return TRUE;
}

bool Core::InitWindow(HINSTANCE hInstance, int nCmdShow)
{
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow)) return false;
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);

    if (!Graphics::Get()->Init()) return false;

    Time::Get()->Init();
    World::Get()->Init();
    InputManager::Get()->Init();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    static_cast<void>(io);
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.Fonts->AddFontFromFileTTF(".\\Fonts\\NanumBarunGothic.ttf", 16.f, nullptr, io.Fonts->GetGlyphRangesKorean());
    io.Fonts->AddFontFromFileTTF(".\\Fonts\\NanumBarunGothicBold.ttf", 16.f, nullptr, io.Fonts->GetGlyphRangesKorean());
    io.Fonts->AddFontFromFileTTF(".\\Fonts\\NanumBarunGothicLight.ttf", 16.f, nullptr,
                                 io.Fonts->GetGlyphRangesKorean());
    io.Fonts->AddFontFromFileTTF(".\\Fonts\\NanumBarunGothicUltraLight.ttf", 16.f, nullptr,
                                 io.Fonts->GetGlyphRangesKorean());

    io.FontDefault = io.Fonts->Fonts[0];

    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(hWnd_);
    ImGui_ImplDX11_Init(Graphics::Get()->GetD3DDevice(), Graphics::Get()->GetD3DDeviceContext());

    logic_handle_ = CreateThread(nullptr, 0, LogicThread, nullptr, 0, nullptr);

    return true;
}

LRESULT Core::StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return Get()->WndProc(hWnd, message, wParam, lParam);
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT Core::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam)) return 0;

    if (message == WM_CREATE)
    {
#ifdef _DEBUG
        AllocConsole();
        SetConsoleTitle(L"Debug Console");

        _tfreopen(L"CONOUT$", L"w", stdout);
#endif
        return 0;
    }

    if (message == WM_SETFOCUS || message == WM_KILLFOCUS)
    {
        focus_ = GetFocus();
        return 0;
    }

    if (message == WM_GETMINMAXINFO)
    {
        reinterpret_cast<MINMAXINFO*>(lParam)->ptMinTrackSize.x = window_area_.right - window_area_.left;
        reinterpret_cast<MINMAXINFO*>(lParam)->ptMinTrackSize.y = window_area_.bottom - window_area_.top;
        reinterpret_cast<MINMAXINFO*>(lParam)->ptMaxTrackSize.x = window_area_.right - window_area_.left;
        reinterpret_cast<MINMAXINFO*>(lParam)->ptMaxTrackSize.y = window_area_.bottom - window_area_.top;

        return 0;
    }

    if (message == WM_DESTROY)
    {
        is_running_ = false;
        WaitForSingleObject(logic_handle_, INFINITE);

        ImGui_ImplWin32_Shutdown();
        ImGui_ImplDX11_Shutdown();
        ImGui::DestroyContext();

        InputManager::Get()->Release();
        World::Get()->Release();
        Time::Get()->Release();
        Graphics::Get()->Release();
        EventManager::Get()->Release();
        Get()->Release();

        CoUninitialize();
        PostQuitMessage(0);
        return 0;
    }

    if (message == WM_CLOSE)
    {
#ifdef _DEBUG
        FreeConsole();
#endif
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

DWORD Core::LogicThread(LPVOID lpParam)
{
    Get()->is_running_ = true;
    while (Get()->is_running_)
    {
        Get()->MainLogic();
    }

    return 0;
}

void Core::MainLogic()
{
    Time::Get()->Tick();

    Graphics::Get()->BeginFrame3D();

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    Tick(Time::DeltaTime());

    Graphics::Get()->BeginFrame2D();

    Render();

    Graphics::Get()->EndFrame2D();

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    Graphics::Get()->EndFrame3D();

    World::Get()->Destroy();
    EventManager::Get()->Tick();
}

void Core::Tick(float delta_time)
{
    InputManager::Get()->Tick();
    
    static float accumulator = 0.f;
    // 죽음의 나선형을 방지하기 위해 최대 프레임 시간을 0.25초로 제한
    const float frame_time = min(delta_time, .25f);
    accumulator += frame_time;

    while (accumulator >= FIXED_TIME_STEP)
    {
        World::Get()->PhysicsTick(FIXED_TIME_STEP);
        accumulator -= FIXED_TIME_STEP;
    }
    
    // 물리 시뮬레이션으로 인해 발생한 오차를 보정하기 위해 보간을 수행
    const float alpha = accumulator / FIXED_TIME_STEP;
    World::Get()->Interpolate(alpha);
    
    World::Get()->Tick(delta_time);

    // Camera 2D 테스트
    Graphics* gfx = Graphics::Get();

    if (ImGui::Begin("Camera"))
    {
        ImGui::Text("Camera Settings");
    
        static int size = 5.f;
        if (ImGui::SliderInt("Size", &size, 1, 10))
        {
            gfx->GetCamera2D().SetProjectionValues(size, .3f, 1000.f);
        }

        static float position[3];
        if (ImGui::InputFloat3("Position", position))
        {
            gfx->GetCamera2D().SetPosition(position[0], position[1], position[2]);
        }

        static float rotation[3];
        if (ImGui::InputFloat3("Rotation", rotation))
        {
            gfx->GetCamera2D().SetRotation(rotation[0], rotation[1], rotation[2]);
        }
    }

    ImGui::End();

    InputManager* input = InputManager::Get();
    float spd = 1.f;
    
    if (input->IsKeyPressed(0x41))
    {
        gfx->GetCamera2D().AdjustPosition(-spd * delta_time, 0.f, 0.f);
    }

    if (input->IsKeyPressed(0x44))
    {
        gfx->GetCamera2D().AdjustPosition(spd * delta_time, 0.f, 0.f);
    }

    if (input->IsKeyPressed(0x57))
    {
        gfx->GetCamera2D().AdjustPosition(0.f, spd * delta_time, 0.f);
    }

    if (input->IsKeyPressed(0x53))
    {
        gfx->GetCamera2D().AdjustPosition(0.f, -spd * delta_time, 0.f);
    }
}

void Core::Render()
{
    World::Get()->Render();
}
