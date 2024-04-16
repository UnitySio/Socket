#pragma once
#include <string>

enum class EndPlayReason : size_t;
class ActorComponent
{
public:
    ActorComponent(class Actor* owner, const std::wstring& kName);
    virtual ~ActorComponent() = default;

    virtual inline void InitializeComponent() {};
    virtual inline void UninitializeComponent() {};
    virtual inline void BeginPlay() {};
    virtual inline void EndPlay(EndPlayReason type) {};
    virtual inline void TickComponent(float delta_time) {};
    virtual inline void Render() {};

    inline Actor* GetOwner() const { return owner_; }

    inline std::wstring GetName() const { return name_; }

private:
    Actor* owner_;

    std::wstring name_;
    
};
