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
    friend class Core;
    friend class GameEngine;
    friend class World;
    friend class UIBase;

    void OnResize(MathTypes::uint32 width, MathTypes::uint32 height);
    void Tick(float deltaTime);
    void Render();
    void Clear();

    MathTypes::uint32 width_;
    MathTypes::uint32 height_;

    std::vector<std::shared_ptr<UIBase>> uis_;
    
};
