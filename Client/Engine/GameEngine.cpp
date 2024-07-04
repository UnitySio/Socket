#include "GameEngine.h"

#include "ProjectSettings.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "Level/Level.h"
#include "Level/World.h"
#include "tmxlite/TileLayer.hpp"
#include "Windows/WindowsWindow.h"
#include "Windows/DX/Renderer.h"
#include "Windows/DX/Shape.h"
#include "Windows/DX/ShapeBatch.h"
#include "../Canvas.h"


GameEngine::GameEngine() :
    game_window_(nullptr),
    shape_batch_(nullptr)
{
}

GameEngine::~GameEngine()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void GameEngine::Init(const SHARED_PTR<WindowsWindow>& window)
{
    game_window_ = window;
    World::Get()->Init(game_window_);

    shape_batch_ = MAKE_SHARED<ShapeBatch>();
    CHECK_IF(shape_batch_, L"Failed to create ShapeBatch.");
    shape_batch_->Init();
    
#pragma region ImGui 초기화
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    
    ImGuiIO& io = ImGui::GetIO(); static_cast<void>(io);
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.Fonts->AddFontFromFileTTF(".\\Game_Data\\NanumBarunGothic.ttf", 16.0f, nullptr, io.Fonts->GetGlyphRangesKorean());
    io.FontDefault = io.Fonts->Fonts[0];

    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(game_window_->GetHWnd());
    ImGui_ImplDX11_Init(Renderer::Get()->GetDevice(), Renderer::Get()->GetDeviceContext());
#pragma endregion
    
}

void GameEngine::GameLoop(float delta_time)
{
    static float accumulator = 0.f;
    float alpha = 0.f;
    
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

#pragma region Tick
    // 죽음의 나선형을 방지하기 위해 delta_time을 제한
    const float kLimitFrameTime = min(delta_time, .25f);
    accumulator += kLimitFrameTime;

    while (accumulator >= ProjectSettings::kFixedTimeStep)
    {
        World::Get()->PhysicsTick(ProjectSettings::kFixedTimeStep);
        accumulator -= ProjectSettings::kFixedTimeStep;
    }

    // 물리 시뮬레이션으로 인해 발생한 오차를 보정하기 위해 alpha를 계산
    alpha = accumulator / ProjectSettings::kFixedTimeStep;
    World::Get()->Tick(delta_time);
    World::Get()->PostTick(delta_time);
#pragma endregion

#pragma region Render
    ImGui::Render();
    
    Renderer::Get()->BeginRender(game_window_);
    World::Get()->Render(alpha);
    
    /*SHARED_PTR<Shape> shape = MAKE_SHARED<Shape>();
    shape->SetVertices(vertices_);
    shape->SetIndices(indices_);
    shape->SetTexture(tilemap_texture_);
    shape->SetScale({.0167f, .0167f});
    shape->SetZOrder(1);*/
    
    /*World::Get()->AddShape(shape);*/

    
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    Renderer::Get()->BeginRenderD2D(game_window_);
    World::Get()->RenderUI();
    Renderer::Get()->EndRenderD2D();
    Renderer::Get()->EndRender();
    //Canvas::Get()->ClearMsg();

#pragma endregion
    
}

void GameEngine::OnQuit()
{
    World::Get()->GetLevel()->Unload(EndPlayReason::kQuit);
}
