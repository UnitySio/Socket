#pragma once
#include "../Enums.h"
#include "../Singleton.h"

enum class SceneType : size_t;
class Level;

class LevelManager : public Singleton<LevelManager>
{
public:
    LevelManager();
    virtual ~LevelManager() override = default;

    void Init();
    void CreateScene(Level* level, SceneType type);
    void LoadScene(SceneType type);
    void Tick(float delta_time);
    void Render();
    void Destroy();

    inline Level* GetLevel() const { return current_level_; }

private:
    Level* current_level_;
    std::unique_ptr<Level> levels_[static_cast<size_t>(SceneType::kEnd)];
    
};
