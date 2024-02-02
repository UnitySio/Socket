#include "SceneManager.h"

#include "Scene.h"
#include "../../Game/Map/MainMap.h"

SceneManager::SceneManager() : current_scene_(nullptr), scenes_{}
{
}

void SceneManager::Init()
{
    Scene* main_map = new MainMap(L"MainMap");
    CreateScene(main_map, SceneType::kDefault);

    LoadScene(SceneType::kDefault);
}

void SceneManager::CreateScene(Scene* scene, SceneType type)
{
    scenes_[static_cast<size_t>(type)] = std::unique_ptr<Scene>(scene);
}

void SceneManager::LoadScene(SceneType type)
{
    if (current_scene_)
    {
        current_scene_->EndPlay();
    }

    current_scene_ = scenes_[static_cast<size_t>(type)].get();
    current_scene_->BeginPlay();
}

void SceneManager::Tick(float delta_time)
{
    if (current_scene_)
    {
        current_scene_->Tick(delta_time);
    }
}

void SceneManager::Render()
{
    if (current_scene_)
    {
        current_scene_->Render();
    }
}

void SceneManager::Destroy()
{
    if (current_scene_)
    {
        current_scene_->Destroy();
    }
}
