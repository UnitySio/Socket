﻿#pragma once
#include <iostream>
#include <memory>

#define SAFE_RELEASE(p) \
    if (p) \
    { \
        delete p; \
        p = nullptr; \
    }

#define CHECK(condition) \
    if (!(condition)) \
    { \
        std::cerr << "Assertion failed: (" #condition "), function " << __FUNCTION__ \
            << ", file " << __FILE__ << ", line " << __LINE__ << std::endl; \
        std::abort(); \
    }

#define CHECK_IF(condition, format, ...) \
    if (!(condition)) \
    { \
        wchar_t buffer[256]; \
        swprintf(buffer, sizeof(buffer), format, __VA_ARGS__); \
        std::wcerr << L"Assertion failed: (" #condition L"), function " << __FUNCTIONW__ \
            << L", file " << __FILEW__ << L", line " << __LINE__ << L".\n" \
            << L"Message: " << buffer << std::endl; \
        std::abort(); \
    }

#define UniquePtr std::unique_ptr
#define SharedPtr std::shared_ptr
#define WeakPtr std::weak_ptr
#define MakeUnique std::make_unique
#define MakeShared std::make_shared
