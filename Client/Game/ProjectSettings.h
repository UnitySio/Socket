#pragma once
#include <map>

#include "Math/MathTypes.h"

// 현재 헤더파일에 있는 타입들은 프로젝트에 종속적인 타입들입니다.
enum class ActorTag : size_t
{
    kNone,
};

enum ActorLayer : MathTypes::uint16
{
    kDefault = 0x0001,
    kFloor = 0x0002,
};

class ProjectSettings
{
public:
    static inline constexpr bool kShowFrameRate = true; // 프레임레이트 표시 여부
    static inline constexpr bool kUseVSync = false; // 수직동기화 사용 여부

    static inline constexpr float kFixedTimeStep = .02f; // 고정 프레임 간격

    static inline const std::map<MathTypes::uint16, MathTypes::uint16> kLayerCollisionMatrix = { // 레이어 충돌 매트릭스
        {kDefault, kDefault | kFloor},
        {kFloor, kDefault | kFloor},
    };
    
    static inline const std::map<std::wstring, std::wstring> kPath = { // 경로
        {L"GameData", L".\\Game_Data\\"},
    };
    
};
