#pragma once
#include "Singleton.h"

class Editor : public Singleton<Editor>
{
public:
    Editor();
    virtual ~Editor() override = default;

    void Tick(float delta_time);
    
};
