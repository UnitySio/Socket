#pragma once
#include "Singleton.h"

class Editor : public Singleton<Editor>
{
public:
    Editor();
    virtual ~Editor() override = default;

    void Tick(float delta_time);

private:
    void OpenSpriteAnimator(bool* p_open);
    
    bool show_sprite_animator_;

    class Texture* sprite_sheet_;
    
};
