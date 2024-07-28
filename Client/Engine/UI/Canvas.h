#pragma once
#include <vector>

#include "Singleton.h"
#include "Math/Vector2.h"

class Widget;

class Canvas : public Singleton<Canvas>
{
public:
    Canvas();
    virtual ~Canvas() override = default;

    void AddWidget(const std::shared_ptr<Widget>& kWidget);

    float GetScaleRatio() const;

    Widget* GetWidgetAtPosition(const Math::Vector2& kPosition);

private:
    friend class Core;
    friend class GameEngine;
    friend class World;
    friend class Widget;

    void OnResize(MathTypes::uint32 width, MathTypes::uint32 height);
    void Tick();
    void Render();
    void Clear();

    MathTypes::uint32 width_;
    MathTypes::uint32 height_;
    MathTypes::uint32 reference_resolution_width_;
    MathTypes::uint32 reference_resolution_height_;

    float match_mode_;

    std::vector<std::shared_ptr<Widget>> widgets_;
    
};
