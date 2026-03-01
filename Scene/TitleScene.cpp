#include "TitleScene.h"
#include "BaseScene.h"
#include <DxLib.h>
#include "../MyDxLib.h"
#include "../Manager/SceneManager.h"
#include "../Library/TextUtil.h"
#include "../Library/Input.h"

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
        TextUtil::DrawFixText(TextDrawType::CENTER, Screen::WIDTH / 2, Screen::HEIGHT / 2, 30, GetColor(255, 255, 255), "ゲームを開始するにはスペースキーを押してください");
        
    }
}

void TitleScene::Init() {
    count = 0;
}

void TitleScene::Release()
{
}
