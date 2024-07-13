#pragma once
#include <Windows.h>

#include "Singleton.h"
#include "Math/MathTypes.h"

class Mouse : public Singleton<Mouse>
{
public:
    Mouse();
    virtual ~Mouse() override = default;

private:
    friend class Core;
    
    bool ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result);

    // 스레드로 부터 안전을 위한 뮤텍스
    std::mutex mutex_;
    
};
