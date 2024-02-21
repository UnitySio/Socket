#include "World.h"

#include "Level.h"
#include "../../Game/Map/MainMap.h"

World::World() : current_level_(nullptr), levels_{}
{
}

void World::Init()
{
    AddLevel<MainMap>(LevelType::kDefault, L"MainMap");

    OpenLevel(LevelType::kDefault);
}

void World::OpenLevel(LevelType type)
{
    if (current_level_)
    {
        current_level_->EndPlay();
    }

    current_level_ = levels_[static_cast<size_t>(type)].get();
    current_level_->BeginPlay();
}

void World::FixedUpdate()
{
}

void World::Tick(float delta_time)
{
    if (current_level_)
    {
        current_level_->Tick(delta_time);
    }
}

void World::Render()
{
    if (current_level_)
    {
        current_level_->Render();
    }
}

void World::Destroy()
{
    if (current_level_)
    {
        current_level_->Destroy();
    }
}
