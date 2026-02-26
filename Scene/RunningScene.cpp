#include "RunningScene.h"
#include "BaseScene.h"
#include "../Manager/ObjectManager.h"
#include "../Object/Player.h"
#include "../Object/ExplosionEffect.h"
#include "../Object/Enemy.h"
#include "../Library/ObjectFactory.h"
#include "../Input.h"

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
}

void RunningScene::Draw() {
    ObjectManager& objManager = ObjectManager::GetInstance();
    objManager.DrawObject(GetName());
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
}
