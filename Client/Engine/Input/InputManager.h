#pragma once

#include "../Singleton.h"
#include "Key.h"

#include <map>

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
