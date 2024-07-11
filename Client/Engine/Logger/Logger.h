#pragma once
#include <vector>

#include "Singleton.h"

class Logger : public Singleton<Logger>
{
public:
    Logger();
    virtual ~Logger() override = default;

    void Render();
    void AddLog(std::wstring format, ...);

private:
    std::vector<std::string> logs_;
    
};
