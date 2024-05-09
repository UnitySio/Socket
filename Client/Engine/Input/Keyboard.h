#pragma once
#include <map>

#include "Singleton.h"
#include "Math/MathTypes.h"

struct KeyState
{
    bool was_down = false;
    bool is_down = false;
};

class Keyboard : public Singleton<Keyboard>
{
public:
    Keyboard();
    virtual ~Keyboard() override = default;

    void Tick();

    void RegisterKey(MathTypes::uint32 key_code);
    void UnregisterKey(MathTypes::uint32 key_code);

    bool IsKeyDown(MathTypes::uint32 key_code) const;
    bool IsKeyUp(MathTypes::uint32 key_code) const;
    bool IsKeyPressed(MathTypes::uint32 key_code) const;

private:
    std::map<MathTypes::uint32, KeyState> key_states_;
    
};
