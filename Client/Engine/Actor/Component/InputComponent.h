#pragma once
#include <map>

#include "ActorComponent.h"
#include "Math/MathTypes.h"
#include "Math/Vector2.h"

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

    inline const Math::Vector2& GetMousePosition() const { return mouse_position_; }

private:
    struct KeyState
    {
        bool was_down = false;
        bool is_down = false;
    };
    
    std::map<MathTypes::uint32, KeyState> key_states_;

    Math::Vector2 mouse_position_;
    
};
