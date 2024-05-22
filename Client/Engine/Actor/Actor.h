#pragma once
#include <memory>
#include <string>
#include <vector>

#include "ProjectSettings.h"
#include "Math/Vector2.h"
#include "Component/ActorComponent.h"

enum class EndPlayReason : size_t;
class TransformComponent;

class Actor
{
public:
    Actor(const std::wstring& kName);
    virtual ~Actor() = default;

    virtual inline void PreInitializeComponents() {};
    virtual inline void PostInitializeComponents() {};
    
    virtual void OnCollisionEnter(Actor* other);
    virtual void OnCollisionStay(Actor* other);
    virtual void OnCollisionExit(Actor* other);
    virtual void OnTriggerEnter(Actor* other);
    virtual void OnTriggerStay(Actor* other);
    virtual void OnTriggerExit(Actor* other);
    virtual void BeginPlay();
    virtual void EndPlay(EndPlayReason type);
    virtual void PhysicsTick(float delta_time);
    virtual void Tick(float delta_time);
    virtual void Render(float alpha);

    void AttachToActor(Actor* actor);
    void DetachFromActor();
    void Destroy();
    void Destroy(const Actor* kOther);
    void SpawnActor(const Actor* kActor);
    void SetActive(bool active);

    bool CompareTag(ActorTag tag) const;

    template <typename T>
    T* CreateComponent(const std::wstring& kName);

    // 추후 리플렉션으로 변경
    template <typename T>
    T* GetComponent();

    // Reflection 구현 필요
    
    inline void SetTag(ActorTag tag) { tag_ = tag; }
    inline void SetLayer(ActorLayer layer) { layer_ = layer; }

    // 추후 구현 예정
    inline size_t GetUniqueID() const { return -1; }
    inline size_t GetTypeHash() const { return -1; }

    inline const std::wstring& GetName() const { return name_; }

    inline ActorTag GetTag() const { return tag_; }
    inline ActorLayer GetLayer() const { return layer_; }

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
    friend class Pawn;
    friend class DistanceJointComponent;
    friend class FrictionJointComponent;

    void InitializeActor();
    void InitializeComponents();
    void UninitializeComponents();
    void Destroyed();
    void CreateBody();
    
    std::wstring name_;

    ActorTag tag_;
    ActorLayer layer_;

    class b2Body* body_;

    bool is_active_;
    bool is_destroy_;

    std::vector<std::shared_ptr<ActorComponent>> components_;

    TransformComponent* transform_;

    Actor* parent_;
    std::vector<Actor*> children_;

    class b2Joint* parent_joint_;
    
};

template <typename T>
T* Actor::CreateComponent(const std::wstring& kName)
{
    components_.push_back(std::make_shared<T>(this, kName));
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
