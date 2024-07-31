#include "pch.h"
#include "MainMenu.h"

#include "Enums.h"
#include "Level/World.h"

MainMenu::MainMenu(const std::wstring& kName) :
    Level(kName)
{
}

void MainMenu::Load()
{
    World::Get()->OpenLevel(LevelType::kDefault);
}
