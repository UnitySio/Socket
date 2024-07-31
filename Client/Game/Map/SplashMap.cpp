#include "pch.h"
#include "SplashMap.h"

#include "Level/World.h"
#include "Resource/ResourceManager.h"
#include "UI/Canvas.h"
#include "UI/Widget/Image.h"
#include "Windows/DX/UITexture.h"

SplashMap::SplashMap(const std::wstring& kName)
    : Level(kName)
{
}

void SplashMap::Load()
{
    ResourceManager::Get()->Load<UITexture>(L"FMODLogo", L".\\Game_Data\\FMODLogo.png");
    UITexture* texture = ResourceManager::Get()->GetResource<UITexture>(L"FMODLogo");

    std::shared_ptr<UI::Image> image = std::make_shared<UI::Image>(L"FMODLogo");
    image->SetSize({texture->GetWidth() / 2.f, texture->GetHeight() / 2.f});
    image->SetAnchorPreset(AnchorPresets::kMiddle | AnchorPresets::kCenter, true);
    image->SetTexture(texture);

    Canvas::Get()->AddWidget(image);

    TimerManager::Get()->SetTimer([]()
    {
        World::Get()->OpenLevel(LevelType::kDefault);
    }, 2.f);
}
