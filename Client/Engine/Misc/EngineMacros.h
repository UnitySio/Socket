﻿#pragma once
#include <iostream>

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
        char buffer[256]; \
        snprintf(buffer, sizeof(buffer), format, __VA_ARGS__); \
        std::cerr << "Assertion failed: (" #condition "), function " << __FUNCTION__ \
            << ", file " << __FILE__ << ", line " << __LINE__ << ".\n" \
            << "Message: " << buffer << std::endl; \
        std::abort(); \
    }
