#pragma once
#include "../Enums.h"
#include "../Singleton.h"

enum class LevelType : size_t;
class Level;

class World : public Singleton<World>
{
public:
    World();
    virtual ~World() override = default;

    void Init();
    void OpenLevel(LevelType type);
    void PhysicsTick(float delta_time);
    void Tick(float delta_time);
    void Render();
    void Destroy();

    template<std::derived_from<Level> T>
    T* AddLevel(LevelType type, std::wstring name);

    inline Level* GetLevel() const { return current_level_; }

private:
    Level* current_level_;
    std::unique_ptr<Level> levels_[static_cast<size_t>(LevelType::kEnd)];
    
};

template <std::derived_from<Level> T>
T* World::AddLevel(LevelType type, std::wstring name)
{
    levels_[static_cast<size_t>(type)] = std::make_unique<T>(name);
    return static_cast<T*>(levels_[static_cast<size_t>(type)].get());
}
