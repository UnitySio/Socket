#pragma once
#include "DebugDraw.h"
#include "Enums.h"
#include "Singleton.h"
#include "box2d/b2_world.h"
#include "Listener/ContactListener.h"
#include "Windows/DX/Renderer.h"
#include <type_traits>


class Shape;
class ShapeBatch;
class Level;
class Actor;

class World : public Singleton<World>
{
    using Object = Actor;
public:
    World();
    virtual ~World() override = default;

    void Init(const SHARED_PTR<WindowsWindow>& window);
    void OpenLevel(LevelType type);
    void PhysicsTick(float delta_time);
    void Tick(float delta_time);
    void Render(float alpha);
    void RenderUI();
    void DestroyActor();

    template<typename T>
    SHARED_PTR<T> SpawnActor(const std::wstring& kName, typename std::enable_if<std::is_class<typename std::decay<T>::type>::value>::type* = nullptr);

    template<std::derived_from<Level> T>
    T* AddLevel(LevelType type, std::wstring name);

    inline WindowsWindow* GetWindow() const { return window_.get(); }
    inline Level* GetLevel() const { return current_level_; }

    void AddShape(const SHARED_PTR<Shape>& shape);
    void ObjectProcess();

private:
    friend class Physics;
    friend class Level;
    friend class Actor;
    friend class TilemapComponent;

    SHARED_PTR<WindowsWindow> window_;
    
    SHARED_PTR<ShapeBatch> shape_batch_;
    
    std::vector<SHARED_PTR<Shape>> shapes_;
    
    UNIQUE_PTR<b2World> physics_world_;
    
    ContactListener contact_listener_;
    
    DebugDraw debug_draw_;
    
    Level* current_level_;
    SHARED_PTR<Level> levels_[static_cast<size_t>(LevelType::kEnd)];
    
    std::vector<SHARED_PTR<Object>> spawnList_;
    std::vector<SHARED_PTR<Object>> removeList_;
    
    int fps_;
};

template<typename T>
inline SHARED_PTR<T> World::SpawnActor(const std::wstring& kName, typename std::enable_if<std::is_class<typename std::decay<T>::type>::value>::type*)
{
    static_assert(std::is_base_of<Object, T>::value, "T Must Derived From Object");
    SHARED_PTR<T> object = MAKE_SHARED<T>(kName);
    spawnList_.push_back(object);
    return object;
}

template <std::derived_from<Level> T>
T* World::AddLevel(LevelType type, std::wstring name)
{
    levels_[static_cast<size_t>(type)] = MAKE_SHARED<T>(name);
    return static_cast<T*>(levels_[static_cast<size_t>(type)].get());
}
