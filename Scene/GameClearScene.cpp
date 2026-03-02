#include "GameClearScene.h"
#include "../Library/TextUtil.h"
#include "../Library/Input.h"
#include "../MyDxLib.h"
#include "../Manager/SceneManager.h"

GameClearScene::GameClearScene()
    : BaseScene("GameClearScene") {
    count = 0;
}

GameClearScene::~GameClearScene() {
}

void GameClearScene::Update() {
    count++;
    if (Input::IsKeyDown(KEY_INPUT_SPACE)) {
        SceneManager& sceneManager = SceneManager::GetInstance();
        sceneManager.ChangeScene("TitleScene");
    }
}

void GameClearScene::Draw() {
    if (count % 100 < 50) {
        TextUtil::DrawFixText(TextDrawType::CENTER, Screen::WIDTH / 2, Screen::HEIGHT / 2, 30, GetColor(255, 255, 255), "ゲームクリア!");
        TextUtil::DrawFixText(TextDrawType::CENTER, Screen::WIDTH / 2, Screen::HEIGHT / 2 + 30, 30, GetColor(255, 255, 255), "スペースキーで戻れます!");
    }
}

void GameClearScene::Init() {
}

void GameClearScene::Release() {
}
