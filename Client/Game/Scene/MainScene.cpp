#include "MainScene.h"

#include "../Actor/Ground.h"
#include "../Actor/JointTest.h"
#include "../Actor/Player.h"

MainScene::MainScene(const std::wstring& name) : Scene(name)
{
    Ground* ground = new Ground(GetWorld(), L"Ground");
    Player* player = new Player(GetWorld(), L"Player");
    JointTest* joint_test = new JointTest(GetWorld(), L"JointTest");
    
    AddActor(ground);
    AddActor(player);
    AddActor(joint_test);
}
