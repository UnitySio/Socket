#pragma once
#include "Singleton.h"

class GameInstance : public Singleton<GameInstance>
{
public:
    GameInstance();
    virtual ~GameInstance() override = default;
    
};
