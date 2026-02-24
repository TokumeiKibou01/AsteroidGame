#include "RunningScene.h"
#include "BaseScene.h"
#include "../Manager/ObjectManager.h"
#include "../Object/Player.h"

RunningScene::RunningScene()
    : BaseScene("RunningScene") {
    ObjectManager& instance = ObjectManager::GetInstance();
    Player* player = new Player(PlayerParams::GetStartLoc(), PlayerParams::GetStartVel(), PlayerParams::GetStartDir(),
                                PlayerParams::RADIUS, PlayerParams::OMEGA);
    instance.AddObject(GetName(), player);
}

RunningScene::~RunningScene() {
}

void RunningScene::Update() {
    ObjectManager& objManager = ObjectManager::GetInstance();
    objManager.UpdateObject(GetName());
}

void RunningScene::Draw() {
    ObjectManager& objManager = ObjectManager::GetInstance();
    objManager.DrawObject(GetName());
}

void RunningScene::Init() {
}

void RunningScene::Release() {
}
