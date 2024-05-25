#pragma once
#include "DebugDraw.h"
#include "Enums.h"
#include "Singleton.h"
#include "Listener/ContactListener.h"

class b2World;
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
    void Render(float alpha);
    void DestroyActor();

    template<std::derived_from<Level> T>
    T* AddLevel(LevelType type, std::wstring name);

    inline Level* GetLevel() const { return current_level_; }

private:
    friend class Physics;
    friend class Level;
    friend class DebugDraw;
    friend class Actor;
    
   
    friend class DistanceJointComponent;
    friend class FrictionJointComponent;
    friend class GearJointComponent;
    friend class HingeJointComponent;


    friend class FixedJoint;
    template<typename T, typename U>
    friend class BaseJointComponent;

    friend class MainMap;


    
    std::unique_ptr<b2World> physics_world_;
    
    ContactListener contact_listener_;
    
    DebugDraw debug_draw_;
    
    std::unique_ptr<class PrimitiveBatch> primitive_batch_;
    
    Level* current_level_;
    std::shared_ptr<Level> levels_[static_cast<size_t>(LevelType::kEnd)];
    
};

template <std::derived_from<Level> T>
T* World::AddLevel(LevelType type, std::wstring name)
{
    levels_[static_cast<size_t>(type)] = std::make_shared<T>(name);
    return static_cast<T*>(levels_[static_cast<size_t>(type)].get());
}
