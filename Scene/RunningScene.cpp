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
    Player* player = nullptr;
    HealthUI* healthUI = nullptr;
}

RunningScene::RunningScene()
    : BaseScene("RunningScene") {
}

RunningScene::~RunningScene() {
}

void RunningScene::Update() {
    if (player == nullptr) return;
    float delta = GetDeltaTime();
    objManager.UpdateObject(GetName());

    if (Input::IsKeyDown(KEY_INPUT_A)) {
        objManager.AddObject(GetName(), new Enemy(EnemyType::LARGE, 8));
    }
    if (Input::IsKeyDown(KEY_INPUT_Z)) {
        if (player->GetWeaponRemaing() <= 0) {
            static int viewTime = 5;
            if (viewTime <= 0) {
                viewTime = 5;
            }
            else {
                viewTime -= GetDeltaTime();
                std::string noBullet = "Rキーでリロードしてください";
                TextUtil::DrawFixText(TextDrawType::CENTER, Screen::WIDTH / 2, Screen::HEIGHT / 2 + 30, 30, GetColor(255, 255, 255), -1, noBullet);
            }

        }
        else {
            ObjectFactory::spawnBullet(this, player->GetLocation(), player->GetDirection(), player->GetRadius() + 8.0f);
            player->SetWeaponRemaing(player->GetWeaponRemaing() - 1);
        }
    }
    if (Input::IsKeyDown(KEY_INPUT_R) && !player->IsReloading()) {  
        player->SetIsReloading(true);
    }

    if (player->IsReloading()) {
        std::string reloadText = "リロード中... " + std::to_string(player->GetReloadTime());
        TextUtil::DrawFixText(TextDrawType::CENTER, Screen::WIDTH / 2, Screen::HEIGHT / 2, 30, GetColor(255, 255, 255), -1, reloadText);

        if (player->GetReloadTime() <= 0) {
            player->SetWeaponRemaing(PlayerParams::MAX_WEAPON);
            player->SetReloadTime(PlayerParams::RELOAD_TIME);
            player->SetIsReloading(false);
        } else {
            player->SetReloadTime(player->GetReloadTime() - delta);
            player->SetIsReloading(true);
        }
    }

    player->SetCoolTime(player->GetCoolTime() - delta);
}

void RunningScene::Draw() {
    if (player == nullptr) return;
    auto enemies = objManager.GetDrawObjects<Enemy>(GetName());
    objManager.DrawObject(GetName());

    std::string scoreText = "スコア：" + std::to_string(player->GetScore());
    TextUtil::DrawFixText(TextDrawType::LEFT, 0, 0, 30, GetColor(240, 183, 26), GetColor(0, 0, 0), scoreText, true);
    std::string highScore = "ハイスコア：" + std::to_string(player->GetHighScore());
    TextUtil::DrawFixText(TextDrawType::LEFT, 0, 30, 30, GetColor(240, 183, 26), GetColor(0, 0, 0), highScore, true);

    std::string coolTimeText = "無敵クールタイム：" + std::to_string(player->GetCoolTime());
    TextUtil::DrawFixText(TextDrawType::LEFT, 0, Screen::HEIGHT - 30*2, 30, GetColor(0, 0, 0), GetColor(255, 255, 255), coolTimeText, true);
    std::string bulletRemaing = "残りの弾数：" + std::to_string(player->GetWeaponRemaing());
    TextUtil::DrawFixText(TextDrawType::LEFT, 0, Screen::HEIGHT - 30, 30, GetColor(0, 0, 0), GetColor(255, 255, 255), bulletRemaing, true);

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
    player = new Player(PlayerParams::GetStartLoc(), PlayerParams::GetStartVel(), PlayerParams::GetStartDir(),
        PlayerParams::RADIUS, PlayerParams::OMEGA);

    objManager.AddObject(GetName(), player);

    for (int i = 0; i < EnemyParams::ENEMY_MAX; i++) {
        ObjectFactory::spawnEnemy();
    }

    healthUI = new HealthUI();
    objManager.AddObject(GetName(), healthUI);
}

void RunningScene::Release() {
    objManager.ClearObjects(GetName());
}
