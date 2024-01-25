#pragma once
#include <memory>
#include <vector>

#include "Component/Component.h"

class b2Body;

class Actor
{
public:
    Actor(class b2World* world);
    virtual ~Actor();

    virtual inline void Begin() {};
    virtual inline void Render() {};
    virtual inline void OnCollisionBegin(Actor* other) {};
    virtual inline void OnCollisionEnd(Actor* other) {};
    virtual inline void OnCollision(Actor* other) {};
    virtual inline void OnTriggerBegin(Actor* other) {};
    virtual inline void OnTrigger(Actor* other) {};
    virtual inline void OnTriggerEnd(Actor* other) {};

    virtual void Tick(float deltaTime);

    void Destroy();
    void Destroy(const Actor* other);
    void SpawnActor(const Actor* actor);

    template <typename T>
    T* AddComponent();

    template <typename T>
    T* GetComponent();

    template <typename T>
    std::vector<T*> GetComponents();

    inline void SetName(const char* name) { strcpy_s(name_, name); }
    inline const char* GetName() const { return name_; }

    inline b2Body* GetBody() const { return body_; }

    inline bool IsActive() const { return is_active_; }

    void SetActive(bool active);

private:
    friend class Scene;
    friend class EventManager;
    friend class Component;
    
    char name_[256];

    b2Body* body_;

    bool is_active_;
    bool is_destroy_;

    std::vector<std::unique_ptr<Component>> components_;
    
};

template <typename T>
T* Actor::AddComponent()
{
    components_.push_back(std::make_unique<T>(this));
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
