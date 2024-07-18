#include "pch.h"
#include "Logger.h"

#include "imgui/imgui.h"

Logger::Logger()
{
}

void Logger::AddLog(std::wstring format, ...)
{
    va_list args;
    va_start(args, format);

    wchar_t buffer[256];
    vswprintf_s(buffer, format.c_str(), args);

    std::wcout << buffer << std::endl;
    va_end(args);
}
