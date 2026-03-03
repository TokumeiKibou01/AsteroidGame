#include "GameOverScene.h"
#include "TitleScene.h"
#include "BaseScene.h"
#include <DxLib.h>
#include "../MyDxLib.h"
#include "../Manager/SceneManager.h"
#include "../Library/TextUtil.h"
#include "../Library/Input.h"

namespace {
    SceneManager& sceneManager = SceneManager::GetInstance();
}

GameOverScene::GameOverScene()
    : BaseScene("GameOverScene") {
}

GameOverScene::~GameOverScene() {
}

void GameOverScene::Update() {
    sceneCounter_++;
    if (Input::IsKeyDown(KEY_INPUT_SPACE)) {
        sceneManager.ChangeScene("TitleScene");
    }
}

void GameOverScene::Draw() {
    if (sceneCounter_ % 100 < 50) {
        TextUtil::DrawFixText(TextDrawType::CENTER, Screen::WIDTH / 2, Screen::HEIGHT / 2, 30, GetColor(255, 255, 255), "ゲーム終了!");
        TextUtil::DrawFixText(TextDrawType::CENTER, Screen::WIDTH / 2, Screen::HEIGHT / 2 + 30, 30, GetColor(255, 255, 255), "スペースキーで戻れます!");
    }
}

void GameOverScene::Init() {
}

void GameOverScene::Release() {
}
