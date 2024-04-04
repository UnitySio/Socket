#pragma once
#include <map>

typedef unsigned short uint16;

// 현재 헤더파일에 있는 타입들은 프로젝트에 종속적인 타입들입니다.
enum class ActorTag : size_t
{
    kNone,
};

enum class ActorLayer : uint16
{
    kDefault = 0x0001,
};

class ProjectSettings
{
public:
    static inline const std::wstring kProjectName = L"Game";
    static inline const std::wstring kProjectClassName = L"Game_GE";
    static inline const std::wstring kProjectVersion = L"1.0.0";

    static inline constexpr int kScreenWidth = 640;
    static inline constexpr int kScreenHeight = 480;
    
    static inline constexpr bool kShowFrameRate = true;
    static inline constexpr bool kUseVSync = true;

    static inline const std::map<uint16, uint16> kLayerCollisionMatrix = {
        {0x0001, 0x0001},
    };
    
};
