#include "pch.h"
#include "WorldMap.h"

#include "MainMap.h"
#include "Level/World.h"
#include "Math/Color.h"
#include "Misc/Delegate.h"
#include "UI/Button.h"
#include "UI/Canvas.h"
#include "UI/Text.h"
#include "UI/UIBase.h"

WorldMap::WorldMap(const std::wstring& kName) 
	: 
	Level(kName)
{
}


void WorldMap::Load()
{
	std::shared_ptr<UI::Button> button = std::make_shared<UI::Button>(L"Button");
	button->SetPosition({ 0.f, 0.f });
	button->SetSize({ 180.f, 30.f });
	button->SetAnchorPreset(AnchorPresets::kLeft, true);
	button->on_click.Add(this, &WorldMap::OnCallback);
    
	Canvas::Get()->AddUI(button);

	std::shared_ptr<UI::Text> text = std::make_shared<UI::Text>(L"ButtonText");
	text->SetPosition({ 0.f, 0.f });
	text->SetSize({ 0.f, 0.f });
	text->SetAnchorPreset(AnchorPresets::kStretch, true);
	text->SetColor(Math::Color::Black);
	text->SetText(L"이전 맵");
	text->AttachToUI(button.get());
    
	Canvas::Get()->AddUI(text);
}

void WorldMap::OnCallback()
{
    World::Get()->OpenLevel(LevelType::kDefault);
}
