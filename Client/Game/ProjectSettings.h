#pragma once

// 현재 헤더파일에 있는 타입들은 프로젝트에 종속적인 타입들입니다.
enum class ActorTag
{
    kNone
};

enum class ActorLayer
{
    kDefault
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
    
};
