#include "BootScene.h"
#include "BaseScene.h"
#include "../Object/BoxObject.h"
#include "../Manager/ObjectManager.h"
#include <DxLib.h>
#include "../Library/Location2D.h"
#include "../Manager/AudioManager.h"
#include "../Manager/SceneManager.h"

namespace {
    ObjectManager& objManager = ObjectManager::GetInstance();
}

BootScene::BootScene()
    : BaseScene("BootScene") {
}

BootScene::~BootScene() {
}

void BootScene::Update() {
    sceneCounter_++;
    objManager.UpdateObject(GetName());
}

void BootScene::Draw() {
    objManager.DrawObject(GetName());

    DrawFormatString(0, 0, GetColor(255, 255, 255), "BootScene: %d", sceneCounter_);
}

void BootScene::Init() {
}

void BootScene::Release() {
}
