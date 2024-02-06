#pragma once
#include <string>

class ActorComponent
{
public:
    ActorComponent(class Actor* owner, const std::wstring& kName);
    virtual ~ActorComponent() = default;

    virtual inline void BeginPlay() {};
    virtual inline void EndPlay() {};
    virtual inline void TickComponent(float delta_time) {};
    virtual inline void Render() {};

    class b2World* GetWorld() const;

    inline Actor* GetOwner() const { return owner_; }

    inline std::wstring GetName() const { return name_; }

protected:
    Actor* owner_;

    std::wstring name_;
    
};
