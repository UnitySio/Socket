#pragma once
#include <memory>
#include <string>

#include "Object.h"
#include "Misc/EngineMacros.h"

enum class EndPlayReason : MathTypes::uint64;
class ActorComponent : public Object, public std::enable_shared_from_this<ActorComponent>
{
    SHADER_CLASS_HELPER(ActorComponent)
    
public:
    ActorComponent(class Actor* owner, const std::wstring& kName);
    virtual ~ActorComponent() override = default;

    inline Actor* GetOwner() const { return owner_; }
    inline std::wstring GetName() const { return name_; }

protected:
    virtual inline void InitializeComponent() {};
    virtual inline void UninitializeComponent() {};
    virtual inline void BeginPlay() {};
    virtual inline void EndPlay(EndPlayReason type) {};
    virtual inline void PhysicsTickComponent(float delta_time) {};
    virtual inline void TickComponent(float delta_time) {};
    virtual inline void PostTickComponent(float delta_time) {};
    virtual inline void Render(float alpha) {};
    
    Actor* owner_;
    std::wstring name_;

private:
    friend class Actor;
    friend class PlayerController;
    
};
