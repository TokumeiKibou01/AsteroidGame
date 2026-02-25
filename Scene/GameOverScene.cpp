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
}

GameOverScene::~GameOverScene() {
}

void GameOverScene::Update() {
    count++;
}

void GameOverScene::Draw() {
}

void GameOverScene::Init() {
    count = 0;
}

void GameOverScene::Release()
{
}
