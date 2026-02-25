#include "TitleScene.h"
#include "BaseScene.h"
#include <DxLib.h>
#include "../MathUtil.h"
#include "../MyDxLib.h"
#include "../Input.h"
#include "../Manager/SceneManager.h"

namespace {
    
}

TitleScene::TitleScene()
    : BaseScene("TitleScene") {
    count = 0;
}

TitleScene::~TitleScene() {}

void TitleScene::Update() {
    SceneManager& sceneManager = SceneManager::GetInstance();
    count++;

    if (Input::IsKeepKeyDown(KEY_INPUT_SPACE)) {
        sceneManager.ChangeScene("RunningScene");
    }
}

void TitleScene::Draw() {
    if (count % 100 < 50) {
        int fontSize = GetFontSize();
        DrawString(Screen::WIDTH / 2 - fontSize*10, Screen::HEIGHT / 2, "ゲームを開始するにはスペースキーを押してください", GetColor(255, 255, 255));
    }
}

void TitleScene::Init() {
    count = 0;
}

void TitleScene::Release()
{
}
