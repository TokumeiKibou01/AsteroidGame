#pragma once

#include "Location2D.h"
#include "Vector2D.h"
#include "MathUtil.h"
#include "../Manager/ObjectManager.h"
#include "../Object/ExplosionEffect.h"
#include "../Object/Bullet.h"
#include "../Scene/BaseScene.h"

namespace ObjectFactory {

    inline void spawnPlayer() {

    }

    inline void spawnEffect(const Location2D& loc) {
        ExplosionEffect* effect = new ExplosionEffect(loc);
        ObjectManager& objManager = ObjectManager::GetInstance();
        objManager.AddObject("RunningScene", effect);
    }

    inline void spawnEnemy() {
        Location2D location;

        int side = GetRand(3);
        if (side == 0) { location.x_ = 0.0f; location.y_ = MathUtil::Rand::RandRange(0.0f, Screen::HEIGHT); }
        if (side == 1) { location.x_ = Screen::WIDTH; location.y_ = MathUtil::Rand::RandRange(0.0f, Screen::HEIGHT); } 
        else if (side == 2) { location.x_ = MathUtil::Rand::RandRange(0.0f, Screen::WIDTH); location.y_ = 0.0f; } 
        else if (side == 3) { location.x_ = MathUtil::Rand::RandRange(0.0f, Screen::WIDTH); location.y_ = Screen::HEIGHT; }

        float angle = MathUtil::Rand::RandRange(0.0f, MathUtil::PI_F * 2.0f);
        float speed = MathUtil::Rand::RandRange(EnemyParams::SPEED_MIN, EnemyParams::SPEED_MAX);
        Vector2D velocity;
        velocity.x_ = cosf(angle) * speed;
        velocity.y_ = sinf(angle) * speed;
        int segment = MathUtil::Rand::RandRangeInt(EnemyParams::SEGMENT_MIN, EnemyParams::SEGMENT_MAX);

        ObjectManager& objManager = ObjectManager::GetInstance();
        Enemy* enemy = new Enemy(EnemyType::LARGE, segment);
        objManager.AddObject("RunningScene", enemy);
    }

    inline void spawnDivideEnemy(Enemy* enemy, int count) {
        ObjectManager& objManager = ObjectManager::GetInstance();
        std::vector<Enemy*> enemyList = objManager.GetDrawObjects<Enemy>("RunningScene");
        
        if (enemy->GetEnemyType() != EnemyType::SMALL && EnemyParams::ENEMY_MAX >= enemyList.size()) {
            EnemyType type = enemy->GetEnemyType() == EnemyType::LARGE ? EnemyType::MEDIUM : EnemyType::SMALL;
            for (int n = 0; n < count; n++) { // 大サイズの場合、中サイズ2体を出す
                Enemy* newEnemy = new Enemy(type, 8);
                Vector2D randomVel = { (float)(GetRand(200) - 100), (float)(GetRand(200) - 100) };
                newEnemy->SetLocation(enemy->GetLocation());
                newEnemy->SetVector(randomVel);
                objManager.AddObject("RunningScene", newEnemy);
            }
        }

        objManager.RemoveObject("RunningScene", enemy);
        spawnEffect(enemy->GetLocation());
    }

    inline void spawnBullet(BaseScene* scene, const Location2D& loc, const Vector2D& dir, const float offset) {
        ObjectManager& objManager = ObjectManager::GetInstance();

        Location2D resultLoc;
        resultLoc.x_ = loc.x_ + dir.x_ * offset;
        resultLoc.y_ = loc.y_ + dir.y_ * offset;
        Vector2D resultVec;
        resultVec.x_ = dir.x_ * BulletParams::SPEED;
        resultVec.y_ = dir.y_ * BulletParams::SPEED;

        Bullet* bullet = new Bullet(resultLoc, resultVec, BulletParams::RADIUS, BulletParams::COLOR, BulletParams::LIFE);
        objManager.AddObject(scene->GetName(), bullet);
    }

}