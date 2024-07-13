#pragma once
#include <iostream>

#define START int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)

#define SAFE_RELEASE(p) \
    do { \
        if (p) \
        { \
            delete p; \
            p = nullptr; \
        } \
    } while (0)

#define CHECK(condition) \
    do { \
        if (!(condition)) \
        { \
            std::cerr << "Assertion failed: (" #condition "), function " << __FUNCTION__ \
                << ", file " << __FILE__ << ", line " << __LINE__ << std::endl; \
            std::abort(); \
        } \
    } while (0)

#define CHECK_IF(condition, format, ...) \
    do { \
        if (!(condition)) \
        { \
            wchar_t buffer[256]; \
            swprintf(buffer, sizeof(buffer), format, __VA_ARGS__); \
            std::wcerr << L"Assertion failed: (" #condition L"), function " << __FUNCTIONW__ \
                << L", file " << __FILEW__ << L", line " << __LINE__ << L".\n" \
                << L"Message: " << buffer << std::endl; \
            std::abort(); \
        } \
    } while (0)

#define LOG(format, ...) \
    do { \
        Logger::Get()->AddLog(format, __VA_ARGS__); \
    } while (0)
