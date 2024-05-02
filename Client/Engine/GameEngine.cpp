#include "GameEngine.h"

#include "ProjectSettings.h"
#include "Level/World.h"
#include "Misc/EngineMacros.h"
#include "Windows/WindowsWindow.h"
#include "Windows/D3D/ShapeBatch.h"

GameEngine::GameEngine() :
    game_window_(nullptr)
{
}

void GameEngine::Init(const std::shared_ptr<WindowsWindow>& window)
{
    game_window_ = window;

    game_world_ = std::make_shared<World>();
    CHECK_IF(game_world_, L"Failed to create World.");

    game_world_->Init();
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
#pragma endregion
}
