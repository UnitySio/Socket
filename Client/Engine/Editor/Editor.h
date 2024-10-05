#pragma once
#include "Singleton.h"

class Editor : public Singleton<Editor>
{
public:
    Editor();
    virtual ~Editor() override = default;

    void Tick(float delta_time);

private:
    void DrawLevelWindow(bool* p_open);
    
    bool show_level_;
    
};
