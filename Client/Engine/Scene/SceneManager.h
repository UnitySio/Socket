#pragma once
#include "../Enums.h"
#include "../Singleton.h"

enum class SceneType : size_t;
class Scene;

class SceneManager : public Singleton<SceneManager>
{
public:
    SceneManager();
    virtual ~SceneManager() override = default;

    void Init();
    void CreateScene(Scene* scene, SceneType type);
    void LoadScene(SceneType type);
    void Tick(float delta_time);
    void Render();
    void Destroy();

    inline Scene* GetCurrentScene() const { return current_scene_; }

private:
    Scene* current_scene_;
    std::unique_ptr<Scene> scenes_[static_cast<size_t>(SceneType::kEnd)];
    
};
