#pragma once
#include <memory>
#include <string>
#include <vector>

#include "box2d/b2_math.h"
#include "Component/ActorComponent.h"

class b2Body;

class Actor
{
public:
    Actor(class b2World* world, const std::wstring& name);
    virtual ~Actor();

    virtual inline void Begin() {};
    virtual inline void OnCollisionBegin(Actor* other) {};
    virtual inline void OnCollisionEnd(Actor* other) {};
    virtual inline void OnCollision(Actor* other) {};
    virtual inline void OnTriggerBegin(Actor* other) {};
    virtual inline void OnTrigger(Actor* other) {};
    virtual inline void OnTriggerEnd(Actor* other) {};
    
    virtual void Tick(float delta_time);
    virtual void Render();

    void Destroy();
    void Destroy(const Actor* other);
    void SpawnActor(const Actor* actor);
    void SetActive(bool active);

    b2World* GetWorld() const;

    template <typename T>
    T* CreateComponent(const std::wstring& name);

    template <typename T>
    T* GetComponent();

    template <typename T>
    std::vector<T*> GetComponents();

    template <typename T>
    T* GetComponentByName(const std::wstring& name);

    inline unsigned int GetInstanceID() const { return instance_id_; }

    inline const std::wstring& GetName() const { return name_; }
    
    inline b2World* GetWorld() { return world_; }

    inline b2Body* GetBody() const { return body_; }

    inline bool IsActive() const { return is_active_; }

private:
    friend class Scene;
    friend class EventManager;

    static unsigned int next_instance_id_;

    unsigned int instance_id_;
    
    std::wstring name_;

    b2World* world_;
    b2Body* body_;

    bool is_active_;
    bool is_destroy_;

    std::vector<std::unique_ptr<ActorComponent>> components_;
    
};

template <typename T>
T* Actor::CreateComponent(const std::wstring& name)
{
    components_.push_back(std::make_unique<T>(this, name));
    return static_cast<T*>(components_.back().get());
}

template <typename T>
T* Actor::GetComponent()
{
    for (auto& component : components_)
    {
        if (typeid(*component) == typeid(T))
        {
            return static_cast<T*>(component.get());
        }
    }

    return nullptr;
}

template <typename T>
std::vector<T*> Actor::GetComponents()
{
    std::vector<T*> components;

    for (auto& component : components_)
    {
        if (typeid(*component) == typeid(T))
        {
            components.push_back(static_cast<T*>(component.get()));
        }
    }

    return components;
}

template <typename T>
T* Actor::GetComponentByName(const std::wstring& name)
{
    for (auto& component : components_)
    {
        if (typeid(*component) == typeid(T) && component->GetName().compare(name))
        {
            return static_cast<T*>(component.get());
        }
    }

    return nullptr;
}
