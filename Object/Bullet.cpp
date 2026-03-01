#include "Bullet.h"
#include "../MyDxLib.h"
#include <DxLib.h>
#include "../Library/MathUtil.h"
#include "../Manager/ObjectManager.h"
#include "Enemy.h"
#include "../Library/ObjectFactory.h"
#include "Player.h"

Bullet::Bullet(const Location2D& loc, const Vector2D& vel, float radius, unsigned int color, float lifeTime)
    : Base2DObject("Bullet", loc, vel, Vector2D(), -1, -1, true) {
    color_ = color;
    life_ = lifeTime;
}

Bullet::~Bullet()
{
}

void Bullet::Update() {
    if (!isAlive_) return;
    float dt = GetDeltaTime();
    if (dt > 0.05f) dt = 0.05f;

    // 寿命
    life_ -= dt;

    // 移動（数学座標）
    location_.x_ += vector_.x_ * dt;
    location_.y_ += vector_.y_ * dt;
    isAlive_ = (life_ > 0.0f);


    ObjectManager& objManager = ObjectManager::GetInstance();
    Player* player = objManager.GetDrawObject<Player>("RunningScene");
    for (Enemy* enemy : objManager.GetDrawObjects<Enemy>("RunningScene")) {
        if (IsDistanceCollation(enemy)) {
            int count = GetRand(3) + 2; //1～4
            ObjectFactory::spawnDivideEnemy(enemy, count);
            Dead();
            player->AddScore(enemy);
            break;
        }
    }


    if (location_.x_ < -radius_)           location_.x_ += (Screen::WIDTH + radius_ * 2.0f);
    else if (location_.x_ > Screen::WIDTH + radius_)   location_.x_ -= (Screen::WIDTH + radius_ * 2.0f);

    if (location_.y_ < -radius_)           location_.y_ += (Screen::HEIGHT + radius_ * 2.0f);
    else if (location_.y_ > Screen::HEIGHT + radius_)   location_.y_ -= (Screen::HEIGHT + radius_ * 2.0f);

}

void Bullet::Draw() {
    if (!isAlive_) return;
    Location2D s = MathUtil::WorldToScreen(location_);
    DrawCircleAA(
        s.x_, s.y_,
        radius_,
        16,
        color_,
        TRUE
    );
}
