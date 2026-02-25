#include "RunningScene.h"
#include "BaseScene.h"
#include "../Manager/ObjectManager.h"
#include "../Object/Player.h"
#include "../Object/ExplosionEffect.h"
#include "../Object/Enemy.h"
#include "../Library/ObjectFactory.h"

RunningScene::RunningScene()
    : BaseScene("RunningScene") {
    ObjectManager& instance = ObjectManager::GetInstance();
    Player* player = new Player(PlayerParams::GetStartLoc(), PlayerParams::GetStartVel(), PlayerParams::GetStartDir(),
                                PlayerParams::RADIUS, PlayerParams::OMEGA);
    instance.AddObject(GetName(), player);
}

RunningScene::~RunningScene() {
}

void RunningScene::Update() {
    ObjectManager& objManager = ObjectManager::GetInstance();
    auto player = objManager.GetDrawObject<Player>(GetName());
    objManager.UpdateObject(GetName());

    if (CheckHitKey(KEY_INPUT_SPACE)) {
        Player* p = objManager.GetDrawObject<Player>(GetName());
        objManager.AddObject(GetName(), new ExplosionEffect(p->GetLocation()));
    }

    if (CheckHitKey(KEY_INPUT_Z)) {
        objManager.AddObject(GetName(), new Enemy(EnemyType::LARGE, 8));
    }

    if (CheckHitKey(KEY_INPUT_A)) {
        ObjectFactory::spawnBullet(this, player->GetLocation(), player->GetDirection(), player->GetRadius() + 8.0f);
    }
}

void RunningScene::Draw() {
    ObjectManager& objManager = ObjectManager::GetInstance();
    objManager.DrawObject(GetName());
}

void RunningScene::Init() {
}

void RunningScene::Release() {
}
