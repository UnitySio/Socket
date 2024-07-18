#include "pch.h"
#include "Logger.h"

#include <cstdarg>

#include "Windows.h"

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

void Logger::AddErrorLog(std::wstring format, ...)
{
    va_list args;
    va_start(args, format);

    wchar_t buffer[256];
    vswprintf_s(buffer, format.c_str(), args);

    std::wstring log = L"Error: ";
    log += buffer;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    std::wcerr << log << std::endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    va_end(args);
}

void Logger::AddWarningLog(std::wstring format, ...)
{
    va_list args;
    va_start(args, format);

    wchar_t buffer[256];
    vswprintf_s(buffer, format.c_str(), args);

    std::wstring log = L"Warning: ";
    log += buffer;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    std::wcerr << log << std::endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    va_end(args);
}
