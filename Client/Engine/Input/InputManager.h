#pragma once

#include "../Singleton.h"

#include <map>

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

private:
    std::map<int, Key> key_map_;
    
};
