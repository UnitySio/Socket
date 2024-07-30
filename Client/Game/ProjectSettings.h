#pragma once
#include <map>
#include <string>

#include "Math/MathTypes.h"

// 현재 헤더파일에 있는 타입들은 프로젝트에 종속적인 타입들입니다.
enum class ActorTag : size_t
{
    kNone,
};

enum ActorLayer : MathTypes::uint16
{
    kDefault = (0x01<<0)
};

class ProjectSettings
{
public:
    static inline const std::wstring kWindowTitle = L"Fusion2D"; // 윈도우 타이틀

    static inline constexpr MathTypes::uint32 kScreenWidth = 1280; // 화면 너비
    static inline constexpr MathTypes::uint32 kScreenHeight = 720; // 화면 높이

    static inline constexpr MathTypes::uint32 kCanvasReferenceWidth = 1280;
    static inline constexpr MathTypes::uint32 kCanvasReferenceHeight = 720;
    static inline constexpr float kMatchMode = 0.f;
    
    static inline constexpr bool kShowFrameRate = true; // 프레임레이트 표시 여부
    static inline constexpr bool kUseVSync = false; // 수직동기화 사용 여부

    static inline constexpr float kFixedTimeStep = .02f; // 고정 프레임 간격

    static inline const std::map<MathTypes::uint16, MathTypes::uint16> kLayerCollisionMatrix = { // 레이어 충돌 매트릭스
        {kDefault, kDefault},
    };
    
};
