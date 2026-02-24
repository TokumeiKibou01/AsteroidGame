#include "./Base2DObject.h"
#include "Player.h"
#include "../Library/Location2D.h"
#include "../Library/Vector2D.h"
#include "../MathUtil.h"
#include "../Matrix2D.h"
#include <DxLib.h>
#include "../Input.h"
#include <stdexcept>

namespace {
    const float ACC = 400.0f; //加速度
    const float DAMP = 0.995f; //抵抗（0～1）
    const float MAx__SPEED = 500.0f; //速度の上限
}

Player::Player() {
    throw std::runtime_error("引数ありのコンストラクタから呼んでください");
}

Player::Player(const Location2D& loc, const Vector2D& vel, const Vector2D& dir, float radius, float omega)
    : Base2DObject("Player", loc, vel, dir, radius, omega, true) {
    direction_ = dir;
    radius_ = radius;
    omega_ = omega;
    angle_ = 0.0f;
    vertex_[0] = { 0, 0 }; 
    vertex_[1] = { 0, 0 }; 
    vertex_[2] = { 0, 0 };
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

    for (int i = 0; i < 3; i++)
    {
        //回転行列を使って回転させる
        Matrix2D rMat = Matrix2D::Rotation(angle_);
        Matrix2D tMat = Matrix2D::Translation({ -location_.x_, -location_.y_ }); //原点に移動させる行列
        Matrix2D tmMat = Matrix2D::Translation({ location_.x_, location_.y_ }); //原点に移動させる行列
        Matrix2D M = Matrix2D::Multiply(tmMat, Matrix2D::Multiply(rMat, tMat));
        vertex_[i] = Matrix2D::TransformPoint(vertex_[i], M);
    }
    // angle_ から前方向（数学座標）を作る
    direction_ = MathUtil::FromAngle(angle_ + MathUtil::PI_F * 2 / 2);

    // 上キーで推進（加速度）
    if (Input::IsKeepKeyDown(KEY_INPUT_SPACE))
    {
        vector_.x_ += direction_.x_ * ACC * dt;
        vector_.y_ += direction_.y_ * ACC * dt;
    }

    // 抵抗（任意）
    vector_.x_ *= DAMP;
    vector_.y_ *= DAMP;

    // 速度制限（任意）
    float sp2 = vector_.x_ * vector_.x_ + vector_.y_ * vector_.y_;
    float max_2 = MAx__SPEED * MAx__SPEED;
    if (sp2 > max_2) {
        float inv = MAx__SPEED / sqrtf(sp2);
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

}
