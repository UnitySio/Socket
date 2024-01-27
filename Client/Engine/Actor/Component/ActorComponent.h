#pragma once
#include <string>

class ActorComponent
{
public:
    ActorComponent(class Actor* owner, const std::wstring& name);
    virtual ~ActorComponent() = default;

    virtual inline void Begin() {};
    virtual inline void TickComponent(float delta_time) {};
    virtual inline void Render() {};

    inline std::wstring GetName() const { return name_; }

protected:
    Actor* owner_;

    std::wstring name_;
    
};
