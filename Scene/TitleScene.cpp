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

TitleScene::TitleScene()
    : BaseScene("TitleScene") {
}

TitleScene::~TitleScene() {}

void TitleScene::Update() {
    sceneCounter_++;

    if (Input::IsKeepKeyDown(KEY_INPUT_SPACE)) {
        sceneManager.ChangeScene("RunningScene");
    }
}

void TitleScene::Draw() {
    if (sceneCounter_ % 100 < 50) {
        int fontSize = GetFontSize();
        SetFontThickness(10);
        TextUtil::DrawFixText(TextDrawType::CENTER, Screen::WIDTH / 2, Screen::HEIGHT / 2 - 80, 80, GetColor(161, 31, 31), GetColor(255, 255, 255), "Asteroids", true);
        TextUtil::DrawFixText(TextDrawType::CENTER, Screen::WIDTH / 2, Screen::HEIGHT / 2, 30, GetColor(255, 255, 255), GetColor(0, 0, 0), "ゲームを開始するにはスペースキーを押してください", true);
        
    }
}

void TitleScene::Init() {
}

void TitleScene::Release()
{
}
