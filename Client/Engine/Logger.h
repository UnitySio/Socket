#pragma once
#include "Singleton.h"

class Logger : public Singleton<Logger>
{
public:
    Logger();
    virtual ~Logger() override = default;

    static void Print(const wchar_t* message, ...);
    
};
