#pragma once
#include "Object.h"
#include "box2d/id.h"
#include "Misc/DelegateMacros.h"
#include "Misc/EngineMacros.h"
#include "Time/TimerManager.h"

class ActorComponent;
class Actor;
DECLARE_DELEGATE(ContactSignature, Actor*);

enum class EndPlayReason : MathTypes::uint64;
class TransformComponent;

class Actor : public Object, public std::enable_shared_from_this<Actor>
{
    SHADER_CLASS_HELPER(Actor)
    
public:
    Actor(const std::wstring& kName);
    virtual ~Actor() override = default;

    void Destroy();
    void SetLifeSpan(float life_span);
    
    bool CompareTag(ActorTag tag) const;

    template <std::derived_from<ActorComponent> T>
    T* AddComponent(const std::wstring& kName);

    // 추후 리플렉션으로 변경
    template <std::derived_from<ActorComponent> T>
    T* GetComponent();

    template <std::derived_from<Actor> T>
    T* SpawnActor(const std::wstring& kName);
    
    inline void SetTag(ActorTag tag) { tag_ = tag; }
    inline void SetLayer(ActorLayer layer) { layer_ = layer; }

    inline const std::wstring& GetName() const { return name_; }

    inline ActorTag GetTag() const { return tag_; }
    inline ActorLayer GetLayer() const { return layer_; }

    inline TransformComponent* GetTransform() const { return transform_.get(); }

    inline bool IsPendingDeletion() const { return is_pending_destroy_; }
    
    ContactSignature on_collision_enter;
    ContactSignature on_collision_exit;

    ContactSignature on_trigger_enter;
    ContactSignature on_trigger_exit;

protected:
    friend class Physics2D;
    
    void InitializeActor();
    void InitializeComponents();
    void UninitializeComponents();
    void CreateBody();
    void OnLifeSpanExpired();

    virtual inline void PreInitializeComponents() {};
    virtual inline void PostInitializeComponents() {};
    
    virtual void BeginPlay();
    virtual void EndPlay(EndPlayReason type);
    virtual void Destroyed();

    virtual void PhysicsTick(float delta_time);
    virtual void Tick(float delta_time);
    virtual void PostTick(float delta_time);
    virtual void Render(float alpha);

    virtual void OnCollisionEnter(Actor* other);
    virtual void OnCollisionExit(Actor* other);
    virtual void OnTriggerEnter(Actor* other);
    virtual void OnTriggerExit(Actor* other);

    std::wstring name_;

    ActorTag tag_;
    ActorLayer layer_;

    b2BodyId body_id_;
    b2JointId joint_id_;

    bool is_pending_destroy_;

    std::vector<std::shared_ptr<ActorComponent>> components_;

    std::shared_ptr<TransformComponent> transform_;
    
    TimerHandle life_span_timer_;
private:
    // 추후 정리 예정
    friend class Level;
    friend class ColliderComponent;
    friend class BoxColliderComponent;
    friend class CircleColliderComponent;
    friend class CapsuleColliderComponent;
    friend class SegmentColliderComponent;
    friend class RigidBody2DComponent;
    friend class TransformComponent;
    friend class PlayerController;
    friend class ContactListener;
    friend class World;

};

template <std::derived_from<ActorComponent> T>
T* Actor::AddComponent(const std::wstring& kName)
{
    components_.push_back(std::make_shared<T>(this, kName));
    return static_cast<T*>(components_.back().get());
}

template <std::derived_from<ActorComponent> T>
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

template <std::derived_from<Actor> T>
T* Actor::SpawnActor(const std::wstring& kName)
{
    return World::Get()->SpawnActor<T>(kName);
}

inline bool IsValid(Actor* actor)
{
    return actor && !actor->IsPendingDeletion();
}
