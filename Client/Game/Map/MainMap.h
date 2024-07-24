#pragma once
#include "Level/Level.h"

namespace UI
{
    class Text;
}

class MainMap : public Level
{
public:
    MainMap(const std::wstring& kName);
    virtual ~MainMap() override = default;

    virtual void Load() override;
    virtual void Tick(float delta_time) override;

private:
    void OnCallback();
    
    std::shared_ptr<Actor> player;
    std::shared_ptr<UI::Text> ui;

};
