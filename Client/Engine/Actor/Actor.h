#pragma once
#include <memory>

class b2Body;

class Actor : public std::enable_shared_from_this<Actor>
{
public:
    Actor(class b2World* world);
    Actor(const Actor& kOrigin);
    virtual ~Actor() = default;

    virtual void Begin() = 0;
    virtual void Tick(float deltaTime) = 0;
    virtual void Render() = 0;

    inline void SetName(const char* name) { strcpy_s(name_, name); }
    inline const char* GetName() const { return name_; }

    inline b2Body* GetBody() const { return body_; }

private:
    char name_[256];

    b2Body* body_;
    
};
