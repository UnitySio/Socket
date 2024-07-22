#pragma once
#include <vector>

#include "Singleton.h"

class UIBase;

class Canvas : public Singleton<Canvas>
{
public:
    Canvas();
    virtual ~Canvas() override = default;

    void AddUI(const std::shared_ptr<UIBase>& kUI);

private:
    friend class GameEngine;

    void Render();

    std::vector<std::shared_ptr<UIBase>> uis_;
    
};
