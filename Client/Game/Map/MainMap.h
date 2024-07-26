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

};
