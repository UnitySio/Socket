#pragma once
#include "Singleton.h"

class Editor : public Singleton<Editor>
{
public:
    Editor();
    virtual ~Editor() override = default;

    void Tick(float delta_time);

private:
    void ShowHierarchy(bool* p_open);
    void ShowAnimator(bool* p_open);
    void ShowSpriteEditor(bool* p_open);

    bool show_hierarchy_;
    bool show_animator_;
    bool show_sprite_editor_;

    class Sprite* sprite_;
    
};
