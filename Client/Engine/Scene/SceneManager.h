#pragma once
#include "../Enums.h"
#include "../Singleton.h"

enum class SceneType : size_t;
class Scene;

class SceneManager : public Singleton<SceneManager>
{
public:
    SceneManager();
    virtual ~SceneManager() final = default;

    void Init();
    void CreateScene(std::shared_ptr<Scene> scene, SceneType type);
    void LoadScene(SceneType type);
    void Tick(float deltaTime);
    void Render();
    void Destroy();

    inline Scene* GetCurrentScene() const { return current_scene_.get(); }

private:
    std::shared_ptr<Scene> current_scene_;
    std::shared_ptr<Scene> scenes_[static_cast<size_t>(SceneType::kEnd)];
    
};
