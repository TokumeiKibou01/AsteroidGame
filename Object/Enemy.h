#pragma once
#include "../Object/Base2DObject.h"
#include <vector>

enum class EnemyType {
    SMALL,
    MEDIUM,
    LARGE
};

namespace EnemyParams {
    static const int ENEMY_MAX = 50;
    // 見た目
    constexpr int   SEGMENT_MIN = 12;
    constexpr int   SEGMENT_MAX = 20;
    constexpr float JITTER_MIN = 0.25f;
    constexpr float JITTER_MAX = 0.45f;

    // サイズ
    constexpr float R_MIN = 25.0f;
    constexpr float R_MAX = 60.0f;

    // 移動
    constexpr float SPEED_MIN = 80.0f;
    constexpr float SPEED_MAX = 220.0f;

    // 回転
    constexpr float OMEGA_MIN = -1.2f; // rad/sec
    constexpr float OMEGA_MAX = 1.2f;
    const float MIN_RADIUS = 25.0f; //最小半径
    const float MAX_OMEGA = 2.0f; //最大角速度

    //サイズ定数
    const float SMALL_RADIUS_MIN = 20.0f; //小サイズの最小半径
    const float SMALL_RADIUS_MAX = 40.0f; //小サイズの最大半径
    const float MEDIUM_RADIUS_MIN = 40.0f; //中サイズの最小半径
    const float MEDIUM_RADIUS_MAX = 60.0f; //中サイズの最大半径
    const float LARGE_RADIUS_MIN = 60.0f; //大サイズの最小半径
    const float LARGE_RADIUS_MAX = 80.0f; //大サイズの最大半径
}

class Enemy : public Base2DObject {
private:
    int segment_;
    EnemyType enemyType_;
    float life_;
    std::vector<Location2D> vertex_;

    void RandomRadius(EnemyType type);
public:
    Enemy(EnemyType type, int segment);
    ~Enemy();
    void Update() override;
    void Draw() override;

    EnemyType GetEnemyType() { return enemyType_; };
};