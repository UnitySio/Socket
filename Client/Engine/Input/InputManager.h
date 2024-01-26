#pragma once

#include "../Singleton.h"

#include <map>

#include "box2d/b2_math.h"

enum class KeyState : size_t;

struct Key
{
    KeyState state;
    bool is_down;
};

class InputManager : public Singleton<InputManager>
{
public:
    InputManager();
    virtual ~InputManager() final = default;

    void Init();
    void Tick();

    bool IsKeyDown(int key) const;
    bool IsKeyPressed(int key) const;
    bool IsKeyUp(int key) const;

    inline b2Vec2 GetMousePosition() const { return mouse_position_; }
    inline b2Vec2 GetMouseDelta() const { return mouse_delta_; }

private:
    std::map<int, Key> key_map_;

    b2Vec2 mouse_position_;
    b2Vec2 mouse_previous_position_;;
    b2Vec2 mouse_delta_;
    
};
