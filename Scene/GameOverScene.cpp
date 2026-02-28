#include "GameOverScene.h"
#include "TitleScene.h"
#include "BaseScene.h"
#include <DxLib.h>
#include "../MathUtil.h"
#include "../MyDxLib.h"
#include "../Input.h"
#include "../Manager/SceneManager.h"
#include "../Library/TextUtil.h"

GameOverScene::GameOverScene()
    : BaseScene("GameOverScene") {
    count = 0;
}

GameOverScene::~GameOverScene() {
}

void GameOverScene::Update() {
    count++;
    if (Input::IsKeyDown(KEY_INPUT_SPACE)) {
        SceneManager& sceneManager = SceneManager::GetInstance();
        sceneManager.ChangeScene("TitleScene");
    }
}

void GameOverScene::Draw() {
    if (count % 100 < 50) {
        TextUtil::DrawFixText(TextDrawType::CENTER, Screen::WIDTH / 2, Screen::HEIGHT / 2, 30, GetColor(255, 255, 255), "ゲーム終了!");
        TextUtil::DrawFixText(TextDrawType::CENTER, Screen::WIDTH / 2, Screen::HEIGHT / 2 + 30, 30, GetColor(255, 255, 255), "スペースキーで戻れます!");
    }
}

void GameOverScene::Init() {
    count = 0;
}

void GameOverScene::Release() {
}
