#pragma once
#include <vector>

#include "Singleton.h"

class Widget;

class Canvas : public Singleton<Canvas>
{
public:
    Canvas();
    virtual ~Canvas() override = default;

    void AddWidget(const std::shared_ptr<Widget>& kWidget);

    float GetScaleRatio() const;

private:
    friend class Core;
    friend class GameEngine;
    friend class World;
    friend class Widget;

    void OnResize(MathTypes::uint32 width, MathTypes::uint32 height);
    void Tick(float delta_time);
    void Render();
    void Clear();

    MathTypes::uint32 width_;
    MathTypes::uint32 height_;
    MathTypes::uint32 reference_resolution_width_;
    MathTypes::uint32 reference_resolution_height_;

    float match_mode_;

    std::vector<std::shared_ptr<Widget>> widgets_;

    Widget* hovered_widget_;
    Widget* focused_widget_;
    
};
