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

RunningScene::RunningScene()
    : BaseScene("RunningScene") {
}

RunningScene::~RunningScene() {
}

void RunningScene::Update() {
    ObjectManager& objManager = ObjectManager::GetInstance();
    objManager.UpdateObject(GetName());
    auto player = objManager.GetDrawObject<Player>(GetName());

    if (Input::IsKeyDown(KEY_INPUT_A)) {
        objManager.AddObject(GetName(), new Enemy(EnemyType::LARGE, 8));
    }

    if (player && Input::IsKeyDown(KEY_INPUT_Z)) {
        ObjectFactory::spawnBullet(this, player->GetLocation(), player->GetDirection(), player->GetRadius() + 8.0f);
    }

    player->SetCoolTime(player->GetCoolTime() - GetDeltaTime());
}

void RunningScene::Draw() {
    ObjectManager& objManager = ObjectManager::GetInstance();
    auto player = objManager.GetDrawObject<Player>(GetName());
    objManager.DrawObject(GetName());

    std::string scoreText = "スコア：" + std::to_string(player->GetScore());
    TextUtil::DrawFixText(TextDrawType::LEFT, 0, 0, 30, GetColor(255, 255, 255), scoreText);
    std::string coolTimeText = "クールタイム：" + std::to_string(player->GetCoolTime());
    TextUtil::DrawFixText(TextDrawType::LEFT, 0, 30, 30, GetColor(255, 255, 255), coolTimeText);
    std::string highScore = "ハイスコア：" + std::to_string(player->GetHighScore());
    TextUtil::DrawFixText(TextDrawType::LEFT, 0, 60, 30, GetColor(255, 255, 255), highScore);

    const int healthWidth = 400, healthHeight = 50;
    const int marginX = 30, marginY = 30;
    const int leftX = Screen::WIDTH - marginX - healthWidth, leftY = 0 + marginY;
    const int rightX = Screen::WIDTH - marginX, rightY = marginY + healthHeight;
    const int lineSize = 5;

    //全体の描画
    DrawBox(leftX - lineSize, leftY - lineSize, rightX + lineSize, rightY + lineSize, GetColor(255, 255, 255), true);
    DrawBox(leftX, leftY, rightX, rightY, GetColor(10, 10, 10), true);

    //1個
    const int oneHealthWidth = healthWidth / PlayerParams::MAX_HEART;
    for (int n = 0; n < player->GetHeart(); n++) {
        DrawBox(rightX - (n * oneHealthWidth), leftY, rightX - ((n + 1) * oneHealthWidth), rightY, GetColor(255, 0, 0), true);
    }

    for (int n = 1; n < PlayerParams::MAX_HEART; n++) {
        DrawBox(leftX + (n * oneHealthWidth), leftY, leftX + (n * oneHealthWidth) + lineSize, rightY, GetColor(255, 255, 255), true);
    }

    if (player->GetHeart() <= 0) {
        SceneManager& sceneManager = SceneManager::GetInstance();
        sceneManager.ChangeScene("GameOverScene");
        Release();
    }
}

void RunningScene::Init() {
    ObjectManager& objManager = ObjectManager::GetInstance();
    Player* player = new Player(PlayerParams::GetStartLoc(), PlayerParams::GetStartVel(), PlayerParams::GetStartDir(),
        PlayerParams::RADIUS, PlayerParams::OMEGA);
    objManager.AddObject(GetName(), player);

    for (int i = 0; i < EnemyParams::ENEMY_MAX; i++) {
        ObjectFactory::spawnEnemy();
    }
}

void RunningScene::Release() {
    ObjectManager& objManager = ObjectManager::GetInstance();
    objManager.ClearObjects(GetName());
}
