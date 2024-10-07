#pragma once
#include "Singleton.h"

class Editor : public Singleton<Editor>
{
public:
    Editor();
    virtual ~Editor() override = default;

    void Tick(float delta_time);

private:
    void ShowAnimator(bool* p_open);
    void ShowSpriteEditor(bool* p_open);

    bool show_animator_;
    bool show_sprite_editor_;

    class Sprite* sprite_;
    
};
