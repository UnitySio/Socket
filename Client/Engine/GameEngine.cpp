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
#include "Windows/DX/Texture.h"

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

    if (map_.load(".\\Game_Data\\Tile\\demo.tmx"))
    {
        const auto& tilesets = map_.getTilesets();
        std::wstring tileset_path = std::wstring(tilesets[0].getImagePath().begin(), tilesets[0].getImagePath().end());
        
        tilemap_texture_ = MAKE_SHARED<Texture>();
        CHECK(tilemap_texture_->Load(tileset_path));

        const auto& layers = map_.getLayers();
        const auto& layer = layers[0]->getLayerAs<tmx::TileLayer>();
        const auto map_size = map_.getTileCount();
        const auto tile_size = map_.getTileSize();

        const auto& tileset = map_.getTilesets()[0];
        const auto& tile_ids = layer.getTiles();

        const auto tex_width = tilemap_texture_->GetWidth();
        const auto tex_height = tilemap_texture_->GetHeight();

        const auto tile_count_x = tex_width / tile_size.x;
        const auto tile_count_y = tex_height / tile_size.y;

        const auto u_normal = static_cast<float>(tile_size.x) / tex_width;
        const auto v_normal = static_cast<float>(tile_size.y) / tex_height;
        
        for (auto y = 0u; y < map_size.y; ++y)
        {
            for (auto x = 0u; x < map_size.x; ++x)
            {
                const auto idx = y * map_size.x + x;
                if (idx < tile_ids.size() && tile_ids[idx].ID >= tileset.getFirstGID() &&
                    tile_ids[idx].ID < (tileset.getFirstGID() + tileset.getTileCount()))
                {
                    auto id_index = (tile_ids[idx].ID - tileset.getFirstGID());
                    float u = static_cast<float>(id_index % tile_count_x);
                    float v = static_cast<float>(id_index / tile_count_y);
                    u *= tile_size.x;
                    v *= tile_size.y;

                    u /= tex_width;
                    v /= tex_height;

                    const float tile_pos_x = static_cast<float>(x * tile_size.x);
                    const float tile_pos_y = static_cast<float>(y * tile_size.y);

                    DefaultVertex vertex = {{tile_pos_x, -tile_pos_y, 0.f}, {1.f, 1.f, 1.f, 1.f}, {u, v + v_normal}};
                    vertices_.push_back(vertex);
                    vertex = {{tile_pos_x + tile_size.x, -tile_pos_y, 0.f}, {1.f, 1.f, 1.f, 1.f}, {u + u_normal, v + v_normal}};
                    vertices_.push_back(vertex);
                    vertex = {{tile_pos_x, -tile_pos_y + tile_size.y, 0.f}, {1.f, 1.f, 1.f, 1.f}, {u, v}};
                    vertices_.push_back(vertex);
                    vertex = {{tile_pos_x + tile_size.x, -tile_pos_y + tile_size.y, 0.f}, {1.f, 1.f, 1.f, 1.f}, {u + u_normal, v}};
                    vertices_.push_back(vertex);

                    auto base_index = static_cast<MathTypes::uint32>(vertices_.size() - 4);
                    indices_.push_back(base_index + 0);
                    indices_.push_back(base_index + 1);
                    indices_.push_back(base_index + 2);
                    indices_.push_back(base_index + 2);
                    indices_.push_back(base_index + 1);
                    indices_.push_back(base_index + 3);
                }
            }
        }
    }
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
#pragma endregion

#pragma region Render
    ImGui::Render();
    
    Renderer::Get()->BeginRender(game_window_);
    World::Get()->Render(alpha);
    
    SHARED_PTR<Shape> shape = MAKE_SHARED<Shape>();
    shape->SetVertices(vertices_);
    shape->SetIndices(indices_);
    shape->SetTexture(tilemap_texture_);
    shape->SetScale({.0167f, .0167f});
    shape->SetZOrder(1);
    
    World::Get()->AddShape(shape);
    
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    Renderer::Get()->BeginRenderD2D(game_window_);
    World::Get()->RenderUI();
    Renderer::Get()->EndRenderD2D();
    Renderer::Get()->EndRender();
#pragma endregion
    
}

void GameEngine::OnQuit()
{
    World::Get()->GetLevel()->Unload(EndPlayReason::kQuit);
}
