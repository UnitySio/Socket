#pragma once
#include <memory>

class b2Body;

class Actor : public std::enable_shared_from_this<Actor>
{
public:
    Actor(class b2World* world);
    Actor(const Actor& kOrigin);
    virtual ~Actor() = default;

    virtual inline void Begin() {};
    virtual inline void Tick(float deltaTime) {};
    virtual inline void Render() {};
    virtual inline void OnCollisionBegin(Actor* other) {};
    virtual inline void OnCollisionEnd(Actor* other) {};
    virtual inline void OnCollision(Actor* other) {};
    virtual inline void OnTriggerBegin(Actor* other) {};
    virtual inline void OnTrigger(Actor* other) {};
    virtual inline void OnTriggerEnd(Actor* other) {};

    inline void SetName(const char* name) { strcpy_s(name_, name); }
    inline const char* GetName() const { return name_; }

    inline b2Body* GetBody() const { return body_; }

private:
    char name_[256];

    b2Body* body_;
    
};
