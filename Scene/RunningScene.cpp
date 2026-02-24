#include "RunningScene.h"
#include "BaseScene.h"
#include "../Manager/ObjectManager.h"
#include "../Object/Player.h"

RunningScene::RunningScene()
    : BaseScene("RunningScene") {
    ObjectManager& instance = ObjectManager::GetInstance();
    instance.AddObject(GetName(), new Player());
}

RunningScene::~RunningScene() {
}

void RunningScene::Update() {
}

void RunningScene::Draw() {
}

void RunningScene::Init() {
}

void RunningScene::Release() {
}
