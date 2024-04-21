#pragma once
#include <Windows.h>

#define SAFE_RELEASE(p) \
    if (p) \
    { \
        delete p; \
        p = nullptr; \
    }
