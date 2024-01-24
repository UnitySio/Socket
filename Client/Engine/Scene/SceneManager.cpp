#include "SceneManager.h"

#include "Scene.h"
#include "../../Game/Scene/MainScene.h"

SceneManager::SceneManager()
{
}

void SceneManager::Init()
{
    std::shared_ptr<Scene> main_scene = std::make_shared<MainScene>();
    main_scene->SetName("Map 0");
    CreateScene(main_scene, SceneType::kDefault);
    
    LoadScene(SceneType::kDefault);
}

void SceneManager::CreateScene(std::shared_ptr<Scene> scene, SceneType type)
{
    scenes_[static_cast<size_t>(type)] = scene;
}

void SceneManager::LoadScene(SceneType type)
{
    if (current_scene_)
    {
        current_scene_->End();
    }

    current_scene_ = scenes_[static_cast<size_t>(type)];
    current_scene_->Begin();
}

void SceneManager::Tick(float deltaTime)
{
    if (current_scene_)
    {
        current_scene_->Tick(deltaTime);
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
