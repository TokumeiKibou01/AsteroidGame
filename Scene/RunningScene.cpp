#include "RunningScene.h"
#include "BaseScene.h"
#include "../Object/Player.h"
#include "../Object/ExplosionEffect.h"
#include "../Object/Enemy.h"
#include "../Manager/ObjectManager.h"
#include "../Manager/SceneManager.h"
#include "../Library/ObjectFactory.h"
#include "../Library/TextUtil.h"
#include "../Library/Input.h"
#include "../Object/HealthUI.h"

namespace {
    SceneManager& sceneManager = SceneManager::GetInstance();
    ObjectManager& objManager = ObjectManager::GetInstance();
    Player* player = new Player(PlayerParams::GetStartLoc(), PlayerParams::GetStartVel(), PlayerParams::GetStartDir(),
                                PlayerParams::RADIUS, PlayerParams::OMEGA);
    HealthUI* healthUI = new HealthUI();
}

RunningScene::RunningScene()
    : BaseScene("RunningScene") {
}

RunningScene::~RunningScene() {
}

void RunningScene::Update() {
    if (player == nullptr) return;
    objManager.UpdateObject(GetName());

    if (Input::IsKeyDown(KEY_INPUT_A)) {
        objManager.AddObject(GetName(), new Enemy(EnemyType::LARGE, 8));
    }
    if (Input::IsKeyDown(KEY_INPUT_Z)) {
        ObjectFactory::spawnBullet(this, player->GetLocation(), player->GetDirection(), player->GetRadius() + 8.0f);
    }

    player->SetCoolTime(player->GetCoolTime() - GetDeltaTime());
}

void RunningScene::Draw() {
    if (player == nullptr) return;
    auto enemies = objManager.GetDrawObjects<Enemy>(GetName());
    objManager.DrawObject(GetName());

    std::string scoreText = "スコア：" + std::to_string(player->GetScore());
    TextUtil::DrawFixText(TextDrawType::LEFT, 0, 0, 30, GetColor(255, 255, 255), scoreText);
    std::string coolTimeText = "クールタイム：" + std::to_string(player->GetCoolTime());
    TextUtil::DrawFixText(TextDrawType::LEFT, 0, 30, 30, GetColor(255, 255, 255), coolTimeText);
    std::string highScore = "ハイスコア：" + std::to_string(player->GetHighScore());
    TextUtil::DrawFixText(TextDrawType::LEFT, 0, 60, 30, GetColor(255, 255, 255), highScore);
    if (player->GetHeart() <= 0) {
        sceneManager.ChangeScene("GameOverScene");
        Release();
    }
    if (enemies.size() <= 0) {
        sceneManager.ChangeScene("GameClearScene");
        Release();
    }
}

void RunningScene::Init() {
    objManager.AddObject(GetName(), player);

    for (int i = 0; i < EnemyParams::ENEMY_MAX; i++) {
        ObjectFactory::spawnEnemy();
    }

    objManager.AddObject(GetName(), healthUI);
}

void RunningScene::Release() {
    objManager.ClearObjects(GetName());
}
