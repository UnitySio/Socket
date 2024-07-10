#pragma once
#include "Level/Level.h"

class Button;

class MainMap : public Level
{
public:
    MainMap(const std::wstring& kName);
    virtual ~MainMap() override = default;

    virtual void Load() override;
<<<<<<< HEAD
    

    virtual void Tick(float dt) override;
=======
>>>>>>> 57566bd121a03d52e76d71b4e6a98ffc491806fe

    Button* temp;
};
