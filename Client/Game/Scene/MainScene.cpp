#include "MainScene.h"

#include "../Actor/Ground.h"
#include "../Actor/Player.h"

MainScene::MainScene(const std::wstring& name) : Scene(name)
{
    Ground* ground = new Ground(GetWorld(), L"Ground");
    Player* player = new Player(GetWorld(), L"Player");
    
    AddActor(ground);
    AddActor(player);
}
