#pragma once
#include "../Manager/ObjectManager.h"
#include "../Library/Location2D.h"
#include "../Library/Vector2D.h"
#include "../Object/Bullet.h"
#include "../Scene/BaseScene.h"

namespace ObjectFactory {

    inline void spawnPlayer() {

    }

    inline void spawnEnemy() {

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

    inline void spawnEffect() {

    }
}