#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Vector.h"
#include "Component/ActorComponent.h"

enum class ActorLayer;
enum class ActorTag;
class TransformComponent;

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
    virtual void PhysicsTick(float delta_time);
    virtual void Tick(float delta_time);
    virtual void Render();

    void AttachToActor(Actor* actor);
    void DetachFromActor();
    void Destroy();
    void Destroy(const Actor* kOther);
    void SpawnActor(const Actor* kActor);
    void SetActive(bool active);

    template <typename T>
    T* CreateComponent(const std::wstring& kName);

    // 추후 리플렉션으로 변경
    template <typename T>
    T* GetComponent();

    // Reflection 구현 필요

    // 추후 구현 예정
    inline size_t GetUniqueID() const { return -1; }
    inline size_t GetTypeHash() const { return -1; }

    inline const std::wstring& GetName() const { return name_; }

    inline ActorTag GetTag() const { return tag_; }
    inline ActorLayer GetLayer() const { return layer_; }
    
    inline b2World* GetWorld() { return world_; }

    inline bool IsActive() const { return is_active_; }

    inline TransformComponent* GetTransform() const { return transform_; }

    inline Actor* GetParent() const { return parent_; }

private:
    // 추후 정리 예정
    friend class Level;
    friend class EventManager;
    friend class ColliderComponent;
    friend class RigidBodyComponent;
    friend class TransformComponent;

    void CreateBody();
    
    std::wstring name_;

    ActorTag tag_;
    ActorLayer layer_;

    b2World* world_;

    class b2Body* body_;

    Vector previous_location_;

    float previous_angle_;

    bool is_active_;
    bool is_destroy_;

    std::vector<std::unique_ptr<ActorComponent>> components_;

    TransformComponent* transform_;

    Actor* parent_;
    std::vector<Actor*> children_;

    class b2Joint* parent_joint_;
    
};

template <typename T>
T* Actor::CreateComponent(const std::wstring& kName)
{
    components_.push_back(std::make_unique<T>(this, kName));
    return static_cast<T*>(components_.back().get());
}

template <typename T>
T* Actor::GetComponent()
{
    for (const auto& component : components_)
    {
        if (T* target = dynamic_cast<T*>(component.get()))
        {
            return target;
        }
    }

    return nullptr;
}
