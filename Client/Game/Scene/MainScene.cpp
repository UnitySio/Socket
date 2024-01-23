#include "MainScene.h"

#include "../Actor/Box.h"
#include "../Actor/Ground.h"
#include "../Actor/Player.h"

MainScene::MainScene()
{
    std::shared_ptr<Actor> ground = std::make_shared<Ground>(GetWorld());
    ground->SetName("Ground");
    
    AddActor(ground);

    std::shared_ptr<Actor> player = std::make_shared<Player>(GetWorld());
    player->SetName("Player");

    AddActor(player);

    std::shared_ptr<Actor> box = std::make_shared<Box>(GetWorld());
    box->SetName("Box");

    AddActor(box);
}

void MainScene::Begin()
{
    Scene::Begin();
}

void MainScene::Tick(float deltaTime)
{
    Scene::Tick(deltaTime);
}

void MainScene::Render()
{
    Scene::Render();
}

void MainScene::End()
{
}
