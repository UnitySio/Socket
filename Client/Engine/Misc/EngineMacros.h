#pragma once
#include <iostream>

#define SAFE_RELEASE(p) \
    if (p) \
    { \
        delete p; \
        p = nullptr; \
    }

#define CHECK(condition, message) \
    if (!(condition)) \
    { \
        std::cerr << "Assertion failed: (" #condition "), function " << __FUNCTION__ \
            << ", file " << __FILE__ << ", line " << __LINE__ << ".\n" \
            << "Message: " << message << std::endl; \
        std::abort(); \
    } \
