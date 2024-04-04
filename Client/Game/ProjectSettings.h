﻿#pragma once
#include <map>

typedef unsigned short uint16;

// 현재 헤더파일에 있는 타입들은 프로젝트에 종속적인 타입들입니다.
enum class ActorTag : size_t
{
    kNone,
};

enum ActorLayer : uint16
{
    kDefault = 0x0001,
    kPlayer = 0x0002,
};

class ProjectSettings
{
public:
    static inline const std::wstring kProjectName = L"Game"; // 프로젝트 이름
    static inline const std::wstring kProjectClassName = L"Game_GE"; // 프로젝트 클래스 이름
    static inline const std::wstring kProjectVersion = L"1.0.0"; // 프로젝트 버전

    static inline constexpr int kScreenWidth = 640; // 화면 가로 크기
    static inline constexpr int kScreenHeight = 480; // 화면 세로 크기
    
    static inline constexpr bool kShowFrameRate = true; // 프레임레이트 표시 여부
    static inline constexpr bool kUseVSync = true; // 수직동기화 사용 여부

    static inline const std::map<uint16, uint16> kLayerCollisionMatrix = { // 레이어 충돌 매트릭스
        {kDefault, kDefault | kPlayer},
        {kPlayer, kPlayer | kDefault},
    };
    
};
