g#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Component/ActorComponent.h"

struct Vector;
class SceneComponent;
class b2Body;

class Actor
{
public:
    Actor(class b2World* world, const std::wstring& kName);
    virtual ~Actor() = default;

    virtual inline void OnCollisionEnter(Actor* other) {};
    virtual inline void OnCollisionStay(Actor* other) {};
    virtual inline void OnCollisionExit(Actor* other) {};
    virtual inline void OnTriggerEnter(Actor* other) {};
    virtual inline void OnTriggerStay(Actor* other) {};
    virtual inline void OnTriggerExit(Actor* other) {};
    virtual inline void OnDestroyed() {};
    
    virtual void BeginPlay();
    virtual void EndPlay();
    virtual void Tick(float delta_time);
    virtual void Render();

    void AttachToActor(Actor* actor);
    void Destroy();
    void Destroy(const Actor* other);
    void SpawnActor(const Actor* actor);
    void SetActive(bool active);
    void SetActorLocation(const struct b2Vec2& location);
    void SetActorRotation(float rotation);
    
    bool SetRootComponent(SceneComponent* component);

    Vector GetActorLocation() const;
    Vector GetActorRightVector() const;
    Vector GetActorUpVector() const;

    template <typename T>
    T* CreateComponent(const std::wstring& kName);

    // Reflection 구현 필요

    // 추후 구현 예정
    inline size_t GetUniqueID() const { return 0; }
    inline size_t GetTypeHash() const { return 0; }

    inline SceneComponent* GetRootComponent() const { return root_component_; }

    inline const std::wstring& GetName() const { return name_; }
    
    inline b2World* GetWorld() { return world_; }

    inline bool IsActive() const { return is_active_; }

private:
    // 추후 정리 예정
    friend class Level;
    friend class EventManager;
    friend class SceneComponent;
    friend class ColliderComponent;
    friend class RigidBodyComponent;
    
    std::wstring name_;

    b2World* world_;
    
    b2Body* body_;

    bool is_active_;
    bool is_destroy_;

    SceneComponent* root_component_;
    std::vector<std::unique_ptr<ActorComponent>> components_;
    
};

template <typename T>
T* Actor::CreateComponent(const std::wstring& kName)
{
    components_.push_back(std::make_unique<T>(this, kName));
    return static_cast<T*>(components_.back().get());
}
