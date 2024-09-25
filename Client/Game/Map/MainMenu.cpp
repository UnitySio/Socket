#include "pch.h"
#include "MainMenu.h"

#include "Core.h"
#include "Enums.h"
#include "Level/World.h"
#include "UI/Canvas.h"
#include "UI/Widget/Button.h"
#include "UI/Widget/Text.h"
#include "UI/Widget/TextBox.h"
#include "Windows/WindowsWindow.h"

MainMenu::MainMenu(const std::wstring& kName) :
    Level(kName)
{
}

void MainMenu::Load()
{
    std::shared_ptr<UI::Button> start_button = std::make_shared<UI::Button>(L"New Game");
    start_button->SetAnchorPreset(AnchorPresets::kMiddle | AnchorPresets::kCenter, true);
    start_button->on_click.Add([]()
    {
        World::Get()->OpenLevel(LevelType::kDefault);
    });

    Canvas::Get()->AddWidget(start_button);

    std::shared_ptr<UI::Text> button_text = std::make_shared<UI::Text>(L"New Game Text");
    button_text->SetPosition({0.f, 0.f});
    button_text->SetSize({0.f, 0.f});
    button_text->SetAnchorPreset(AnchorPresets::kStretch, true);
    button_text->AttachToWidget(start_button.get());
    button_text->SetText(L"새 게임");
    button_text->SetColor(Math::Color::Black);

    Canvas::Get()->AddWidget(button_text);

    std::shared_ptr<UI::Button> exit_button = std::make_shared<UI::Button>(L"Exit");
    exit_button->SetPosition({0.f, 45.f});
    exit_button->SetAnchorPreset(AnchorPresets::kMiddle | AnchorPresets::kCenter, true);
    exit_button->on_click.Add([]()
    {
        WindowsWindow* window = World::Get()->GetWindow();
        PostMessage(window->GetHWnd(), WM_USER, 0, 0);
    });

    Canvas::Get()->AddWidget(exit_button);

    std::shared_ptr<UI::Text> exit_button_text = std::make_shared<UI::Text>(L"Exit Text");
    exit_button_text->SetPosition({0.f, 0.f});
    exit_button_text->SetSize({0.f, 0.f});
    exit_button_text->SetAnchorPreset(AnchorPresets::kStretch, true);
    exit_button_text->AttachToWidget(exit_button.get());
    exit_button_text->SetText(L"종료");
    exit_button_text->SetColor(Math::Color::Black);

    Canvas::Get()->AddWidget(exit_button_text);

    std::shared_ptr<UI::TextBox> text_box = std::make_shared<UI::TextBox>(L"Text Box");
    text_box->SetPosition({0.f, -45.f});
    text_box->SetAnchorPreset(AnchorPresets::kMiddle | AnchorPresets::kCenter, true);
    text_box->SetSize({200.f, 30.f});

    Canvas::Get()->AddWidget(text_box);
}
