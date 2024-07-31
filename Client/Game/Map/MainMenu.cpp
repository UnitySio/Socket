#include "pch.h"
#include "MainMenu.h"

#include "Enums.h"
#include "Level/World.h"
#include "UI/Canvas.h"
#include "UI/Widget/Button.h"

MainMenu::MainMenu(const std::wstring& kName) :
    Level(kName)
{
}

void MainMenu::Load()
{
    std::shared_ptr<UI::Button> start_button = std::make_shared<UI::Button>(L"Start Game");
    start_button->SetAnchorPreset(AnchorPresets::kMiddle | AnchorPresets::kCenter);
    start_button->on_click.Add([]()
    {
        World::Get()->OpenLevel(LevelType::kDefault);
    });

    Canvas::Get()->AddWidget(start_button);
}
