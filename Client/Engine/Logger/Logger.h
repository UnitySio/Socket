#pragma once
#include <vector>

#include "Singleton.h"

class Logger : public Singleton<Logger>
{
public:
    Logger();
    virtual ~Logger() override = default;

    void AddLog(std::wstring format, ...);
    void AddErrorLog(std::wstring format, ...);
    void AddWarningLog(std::wstring format, ...);
    
};
