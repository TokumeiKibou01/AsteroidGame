#include "BootScene.h"
#include "BaseScene.h"
#include "../Object/BoxObject.h"
#include "../Manager/ObjectManager.h"
#include <DxLib.h>
#include "../Library/Location2D.h"
#include "../Manager/AudioManager.h"
#include "../Manager/SceneManager.h"

BootScene::BootScene()
    : BaseScene("BootScene") {
    Init();
}

BootScene::~BootScene() {
}

void BootScene::Update() {
    ObjectManager::GetInstance().UpdateObject(GetName());
    auto obj = ObjectManager::GetInstance().GetDrawObject<BoxObject>(GetName());

    Location2D loc = obj->GetLocation();
    loc.x_ += 5;
    obj->SetLocation(loc);

    counter_++;
}

void BootScene::Draw() {
    ObjectManager::GetInstance().DrawObject(GetName());

    DrawFormatString(0, 0, GetColor(255, 255, 255), "BootScene: %d", counter_);
}

void BootScene::Init() {
    counter_ = 0;

    ObjectManager& objManager = ObjectManager::GetInstance();
    objManager.AddObject(GetName(), new BoxObject(Location2D(100.0f, 100.0f), Vector2D(0.0f, 0.0f)));
}

void BootScene::Release() {
}
