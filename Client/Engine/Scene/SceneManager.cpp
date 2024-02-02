#include "SceneManager.h"

#include "Level.h"
#include "../../Game/Map/MainMap.h"

SceneManager::SceneManager() : current_level_(nullptr), levels_{}
{
}

void SceneManager::Init()
{
    Level* main_map = new MainMap(L"MainMap");
    CreateScene(main_map, SceneType::kDefault);

    LoadScene(SceneType::kDefault);
}

void SceneManager::CreateScene(Level* level, SceneType type)
{
    levels_[static_cast<size_t>(type)] = std::unique_ptr<Level>(level);
}

void SceneManager::LoadScene(SceneType type)
{
    if (current_level_)
    {
        current_level_->EndPlay();
    }

    current_level_ = levels_[static_cast<size_t>(type)].get();
    current_level_->BeginPlay();
}

void SceneManager::Tick(float delta_time)
{
    if (current_level_)
    {
        current_level_->Tick(delta_time);
    }
}

void SceneManager::Render()
{
    if (current_level_)
    {
        current_level_->Render();
    }
}

void SceneManager::Destroy()
{
    if (current_level_)
    {
        current_level_->Destroy();
    }
}
