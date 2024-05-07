#include "GameEngine.h"

#include "ProjectSettings.h"
#include "Level/World.h"
#include "Misc/EngineMacros.h"
#include "Windows/WindowsWindow.h"
#include "Windows/D3D/Shape.h"
#include "Windows/D3D/ShapeBatch.h"

GameEngine::GameEngine() :
    game_window_(nullptr)
{
}

void GameEngine::Init(const std::shared_ptr<WindowsWindow>& window)
{
    game_window_ = window;

    game_world_ = std::make_shared<World>(game_window_);
    CHECK_IF(game_world_, L"Failed to create World.");
    game_world_->Init();

    shape_batch_ = std::make_shared<ShapeBatch>();
    CHECK_IF(shape_batch_, L"Failed to create ShapeBatch.");
    shape_batch_->Init();
}

void GameEngine::GameLoop(float delta_time)
{
    static float accumulator = 0.f;
    float alpha = 0.f;

#pragma region Tick
    // 죽음의 나선형을 방지하기 위해 delta_time을 제한
    const float kLimitFrameTime = min(delta_time, .25f);
    accumulator += kLimitFrameTime;

    while (accumulator >= ProjectSettings::kFixedTimeStep)
    {
        game_world_->PhysicsTick(ProjectSettings::kFixedTimeStep);
        accumulator -= ProjectSettings::kFixedTimeStep;
    }

    // 물리 시뮬레이션으로 인해 발생한 오차를 보정하기 위해 alpha를 계산
    alpha = accumulator / ProjectSettings::kFixedTimeStep;
    game_world_->Tick(delta_time);
#pragma endregion

#pragma region Render
    game_world_->Render(alpha);
    
    std::shared_ptr<Shape> shape = std::make_shared<Shape>();

    std::vector<DefaultVertex> vertices;
    vertices.push_back({{0.f, 0.f, 0.f}, {1.f, 1.f, 1.f, 1.f}});

    for (MathTypes::uint32 i = 0; i < 64; ++i)
    {
        const float theta = 2.f * MATH_PI * i / 64;
        const float x = 1.f * cosf(theta);
        const float y = 1.f * sinf(theta);
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

    shape_batch_->DrawShape(game_window_, shape);
    shape.reset();
#pragma endregion
}
