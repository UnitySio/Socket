#pragma once
#include "Singleton.h"
#include "Math/Vector2.h"

class GameInstance : public Singleton<GameInstance>
{
public:
    GameInstance();
    virtual ~GameInstance() override = default;

    Math::Vector2 player_screen_position;
    
};
