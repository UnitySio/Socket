#pragma once

class Component
{
public:
    Component(class Actor* owner);
    virtual ~Component() = default;

    virtual inline void Begin() {};
    virtual inline void TickComponent(float deltaTime) {};
    virtual inline void Render() {};

protected:
    Actor* owner_;

    char name_[256];
    
};
