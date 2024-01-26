#pragma once
#include <string>

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

    std::wstring name_;
    
};
