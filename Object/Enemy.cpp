#include "Enemy.h"
#include <DxLib.h>
#include "../MyDxLib.h"
#include "../Matrix2D.h"
#include "../Library/Location2D.h"
#include "../Library/Vector2D.h"
#include "../MathUtil.h"
#include "../Manager/ObjectManager.h"
#include "../Object/Player.h"

using namespace EnemyParams;

Enemy::Enemy(EnemyType type, int segment)
    : Base2DObject("Enemy", Location2D(), Vector2D(), Vector2D(), -1, -1, true){
    location_ = { (float)GetRand(Screen::WIDTH), (float)GetRand(Screen::HEIGHT) };
    vector_ = { (float)(GetRand(200) - 100), (float)(GetRand(200) - 100) };
    segment_ = segment < EnemyParams::SEGMENT_MIN ? EnemyParams::SEGMENT_MIN : segment;   
    enemyType_ = type;
    RandomRadius(type);
    vertex_.resize(segment_);
    angle_ = 0.0f;
    omega_ = (float)(GetRand(200) - 100) / 100.0f;

    for (int i = 0; i < segment_; i++) {
        float angle = (2.0f * DX_PI / (float)segment_) * (float)i;
        // 半径にランダム性を加える例
        float length = radius_ / 2.0f + GetRand(10);
        vertex_[i] = { cosf(angle) * length, sinf(angle) * length };
    }
}

Enemy::~Enemy() {}

void Enemy::Update() {
    if (!isAlive_) return;
    float dt = GetDeltaTime();
    location_ = location_ + (vector_ * dt);

    if (location_.x_ < 0) location_.x_ = Screen::WIDTH;
    if (location_.x_ > Screen::WIDTH) location_.x_ = 0;
    if (location_.y_ < 0) location_.y_ = Screen::HEIGHT;
    if (location_.y_ > Screen::HEIGHT) location_.y_ = 0;

    angle_ = angle_ + omega_ * dt;

    ObjectManager& objManager = ObjectManager::GetInstance();
    Player* player = objManager.GetDrawObject<Player>("RunningScene");
    if (IsDistanceCollation(player)) {
        player->SetHeart(player->GetHeart() - 1);
        return;
    }
}

void Enemy::Draw() {
    if (!isAlive_) return;
    std::vector<Location2D> scrPos;
    scrPos.resize(segment_);
    for (int i = 0; i < segment_; i++) {
        Location2D worldPos = location_ + vertex_[i];
        Matrix2D rotMat = Matrix2D::Rotation(angle_);
        scrPos[i] = MathUtil::TransformPoint(vertex_[i], rotMat);
        scrPos[i] = scrPos[i] + location_;
        scrPos[i] = MathUtil::WorldToScreen(scrPos[i]);
    }

    for (int i = 0; i < segment_; i++) {
        int next = (i + 1) % segment_;
        DrawLineAA(
            scrPos[i].x_, scrPos[i].y_,
            scrPos[next].x_, scrPos[next].y_,
            GetColor(255, 255, 255), 2.0f
        );
    }
}

void Enemy::RandomRadius(EnemyType type) {
    switch (type) {
    case EnemyType::SMALL:
        radius_ = GetRand((SMALL_RADIUS_MAX - SMALL_RADIUS_MIN)) + SMALL_RADIUS_MIN; //GetRand(40.0 - 20.0) + 20.0：0~20 → 20~40
        break;
    case EnemyType::MEDIUM:
        radius_ = GetRand((MEDIUM_RADIUS_MAX - MEDIUM_RADIUS_MIN)) + MEDIUM_RADIUS_MIN; //GetRand(60.0 - 40.0) + 40.0：0~20 → 40~60;
        break;
    case EnemyType::LARGE:
        radius_ = GetRand((LARGE_RADIUS_MAX - LARGE_RADIUS_MIN)) + LARGE_RADIUS_MIN; //GetRand(80.0 - 60.0) + 60.0：0~20 → 60~80;
        break;
    default:
        radius_ = 1.0f;
        break;
    }
}
