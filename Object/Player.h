#pragma once
#include "Base2DObject.h"
#include "../Library/Location2D.h"
#include "../Library/Vector2D.h"
#include "../MyDxLib.h"
#include <DxLib.h>
#include "../Object/Enemy.h"

namespace PlayerParams {
    const static Location2D GetStartLoc() { return Location2D(Screen::WIDTH / 2, Screen::HEIGHT / 2); } //初期位置
    const static Vector2D GetStartVel() { return { 0.0f, 0.0f }; }
    const static Vector2D GetStartDir() { return { 0.0f, 1.0f }; } //初期の向き（※上）
    const static float RADIUS = 20.0f; //半径
    const static float OMEGA = 2.0f; // 回転速度
    const float ACC = 400.0f; //加速度
    const float DAMP = 0.995f; //抵抗（0～1）
    const float MAx__SPEED = 500.0f; //速度の上限
    static int ENEMY_SCORE[3] = { 20, 50, 100 };
    static int MAX_HEART = 5;
    static float MAX_COOLTIME = 15.0f;
}

class Player : public Base2DObject {
private:
    Location2D vertex_[3]; //3角形の頂点座標
    int score_;
    int highScore_;
    int heart_;
    float coolTime_;
public:
    Player(const Location2D& loc, const Vector2D& vel, const Vector2D& dir, float radius, float omega);
    ~Player();
    void Update() override;
    void Draw() override;

    /// <summary>
    /// 敵の情報を使ってスコア加算
    /// </summary>
    /// <param name="enemy"></param>
    void AddScore(Enemy* enemy);
    void AddScore(int score);
    void SubtractScore(int score);
    void SetScore(int score);
    int GetScore();
    void UpdateHighScore();
    int GetHighScore();

    void SetHeart(int heart);
    int GetHeart();

    void SetCoolTime(float coolTime);
    float GetCoolTime();
    void ResetCoolTime();
};