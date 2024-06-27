#pragma once
#include <map>

#include "ActorComponent.h"
#include "Math/MathTypes.h"

class InputComponent : public ActorComponent
{
public:
    InputComponent(class Actor* owner, const std::wstring& kName);
    virtual ~InputComponent() override = default;

    virtual void TickComponent(float delta_time) override;
    
    void RegisterKey(MathTypes::uint32 key_code);
    void UnregisterKey(MathTypes::uint32 key_code);

    bool IsKeyDown(MathTypes::uint32 key_code) const;
    bool IsKeyUp(MathTypes::uint32 key_code) const;
    bool IsKeyPressed(MathTypes::uint32 key_code) const;

private:
    struct KeyState
    {
        bool was_down = false;
        bool is_down = false;
    };
    
    std::map<MathTypes::uint32, KeyState> key_states_;
    
};
