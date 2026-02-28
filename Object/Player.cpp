#include "./Base2DObject.h"
#include "Player.h"
#include "../Library/Location2D.h"
#include "../Library/Vector2D.h"
#include <DxLib.h>
#undef max //DxLibのwindows.hでマクロが使えないため
#undef min //↑と同様
#include <stdexcept>
#include "Enemy.h"
#include "../Manager/ObjectManager.h"
#include "../DebugWindow/ImGUI/imgui.h"
#include "../Library/MathUtil.h"
#include "../Library/Input.h"
#include <algorithm>

Player::Player(const Location2D& loc, const Vector2D& vel, const Vector2D& dir, float radius, float omega)
    : Base2DObject("Player", loc, vel, dir, radius, omega, true) {
    vertex_[0] = { 0, 0 }; 
    vertex_[1] = { 0, 0 }; 
    vertex_[2] = { 0, 0 };
    score_ = 0;
    heart_ = PlayerParams::MAX_HEART;
    coolTime_ = PlayerParams::MAX_COOLTIME;
}

Player::~Player()
{
}

void Player::Update() {
    const float dt = GetDeltaTime();
    //原点にある半径1の内接する３角形を考える
    Location2D p[3];
    p[0] = { 0.0f, 1.0f };
    p[1] = { cos(MathUtil::ToRadian(-60.0f)), sin(MathUtil::ToRadian(-60.0f)) };
    p[2] = { cos(MathUtil::ToRadian(240.0f)), sin(MathUtil::ToRadian(240.0f)) };
    //半径を１→radius_に拡大
    for (int i = 0;i < 3;i++) {
        p[i] = p[i] * radius_;
    }

    //3角形の3頂点をdir_とradius_とlocation_から求めよう
    vertex_[0] = { location_.x_ + p[0].x_, location_.y_ + p[0].y_ };
    vertex_[1] = { location_.x_ + p[1].x_, location_.y_ + p[1].y_ };
    vertex_[2] = { location_.x_ + p[2].x_, location_.y_ + p[2].y_ };

    if (Input::IsKeepKeyDown(KEY_INPUT_LEFT)) {
        angle_ = angle_ + omega_ * GetDeltaTime();
    }
    if (Input::IsKeepKeyDown(KEY_INPUT_RIGHT)) {
        angle_ = angle_ - omega_ * GetDeltaTime();
    }
    angle_ = fmodf(angle_, MathUtil::PI_F * 2);
    if (angle_ < 0.0f) {
        angle_ += MathUtil::PI_F * 2;
    }

    for (int i = 0; i < 3; i++) {
        //回転行列を使って回転させる
        Matrix2D rMat = Matrix2D::Rotation(angle_);
        Matrix2D tMat = Matrix2D::Translation({ -location_.x_, -location_.y_ }); //原点に移動させる行列
        Matrix2D tmMat = Matrix2D::Translation({ location_.x_, location_.y_ }); //原点に移動させる行列
        Matrix2D M = Matrix2D::Multiply(tmMat, Matrix2D::Multiply(rMat, tMat));
        vertex_[i] = Matrix2D::TransformPoint(vertex_[i], M);
    }
    // angle_ から前方向（数学座標）を作る
    direction_ = MathUtil::FromAngle(angle_ + (MathUtil::PI_F / 2) );

    // 上キーで推進（加速度）
    if (Input::IsKeepKeyDown(KEY_INPUT_SPACE))
    {
        vector_.x_ += direction_.x_ * PlayerParams::ACC * dt;
        vector_.y_ += direction_.y_ * PlayerParams::ACC * dt;
    }

    // 抵抗（任意）
    vector_.x_ *= PlayerParams::DAMP;
    vector_.y_ *= PlayerParams::DAMP;

    // 速度制限（任意）
    float sp2 = vector_.x_ * vector_.x_ + vector_.y_ * vector_.y_;
    float max_2 = PlayerParams::MAx__SPEED * PlayerParams::MAx__SPEED;
    if (sp2 > max_2) {
        float inv = PlayerParams::MAx__SPEED / sqrtf(sp2);
        vector_.x_ *= inv;
        vector_.y_ *= inv;
    }

    // 位置更新（慣性移動）
    location_.x_ += vector_.x_ * dt;
    location_.y_ += vector_.y_ * dt;

    // ----------------------------
// 画面端ワープ（数学座標）
// ----------------------------
    // 半径分だけ外に出たら反対側へ（見た目が自然）
    if (location_.x_ < -radius_) {
        location_.x_ += (Screen::WIDTH + radius_ * 2.0f);
    }
    else if (location_.x_ > Screen::WIDTH + radius_) {
        location_.x_ -= (Screen::WIDTH + radius_ * 2.0f);
    }

    if (location_.y_ < -radius_) {
        location_.y_ += (Screen::HEIGHT + radius_ * 2.0f);
    }
    else if (location_.y_ > Screen::HEIGHT + radius_) {
        location_.y_ -= (Screen::HEIGHT + radius_ * 2.0f);
    }
}

void Player::Draw() {
    Location2D scrPos[3];
    scrPos[0] = MathUtil::WorldToScreen(vertex_[0]);
    scrPos[1] = MathUtil::WorldToScreen(vertex_[1]);
    scrPos[2] = MathUtil::WorldToScreen(vertex_[2]);

    DrawTriangleAA(
        scrPos[0].x_, scrPos[0].y_,
        scrPos[1].x_, scrPos[1].y_,
        scrPos[2].x_, scrPos[2].y_,
        GetColor(255, 0, 0), FALSE, 2.0
    );

    DrawFormatString(50, 50, GetColor(255, 255, 255), "RotAngle:%lf", angle_);
    DrawFormatString(50, 80, GetColor(255, 255, 255), "Velocity:(%lf, %lf)", vector_.x_, vector_.y_);

    ObjectManager objManager = ObjectManager::GetInstance();
    int playerHeart = GetHeart();
    ImGui::Begin("Debug");
    ImGui::SliderInt("プレイヤー", &playerHeart, 1, PlayerParams::MAX_HEART);
    ImGui::End();
    SetHeart(playerHeart);
}

void Player::AddScore(Enemy* enemy) {
    EnemyType type = enemy->GetEnemyType();
    score_ = score_ + PlayerParams::ENEMY_SCORE[(int)type];
}

void Player::AddScore(int score) {
    score_ = score_ + score;
}

void Player::SubtractScore(int score) {
    if (score_ - score >= 0) {
        score_ = score_ - score;
    }
}

void Player::SetScore(int score) {
    if (score >= 0) {
        score_ = score;
    }
}

int Player::GetScore() {
    return score_;
}

void Player::SetHeart(int heart) {
    if (heart >= 0) {
        heart_ = heart;
    }   
}

int Player::GetHeart() {
    return heart_;
}

void Player::SetCoolTime(float coolTime) {
    coolTime_ = std::max(0.0f, coolTime); //例：-1を入れた場合、0.0の方が大きいため0.0が代入される
}

float Player::GetCoolTime() {
    return coolTime_;
}

void Player::ResetCoolTime() {
    coolTime_ = PlayerParams::MAX_COOLTIME;
}
