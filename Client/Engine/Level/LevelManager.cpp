#include "LevelManager.h"

#include "Level.h"
#include "../../Game/Map/MainMap.h"

LevelManager::LevelManager() : current_level_(nullptr), levels_{}
{
}

void LevelManager::Init()
{
    Level* main_map = new MainMap(L"MainMap");
    CreateScene(main_map, SceneType::kDefault);

    LoadScene(SceneType::kDefault);
}

void LevelManager::CreateScene(Level* level, SceneType type)
{
    levels_[static_cast<size_t>(type)] = std::unique_ptr<Level>(level);
}

void LevelManager::LoadScene(SceneType type)
{
    if (current_level_)
    {
        current_level_->EndPlay();
    }

    current_level_ = levels_[static_cast<size_t>(type)].get();
    current_level_->BeginPlay();
}

void LevelManager::Tick(float delta_time)
{
    if (current_level_)
    {
        current_level_->Tick(delta_time);
    }
}

void LevelManager::Render()
{
    if (current_level_)
    {
        current_level_->Render();
    }
}

void LevelManager::Destroy()
{
    if (current_level_)
    {
        current_level_->Destroy();
    }
}
