#pragma once
#include <cmath>
#include "Library/Location2D.h"

struct Matrix2D {
    float m00, m01, tx;
    float m10, m11, ty;
    //    0    0    1

    static Matrix2D Identity() {
        return {
            1, 0, 0,
            0, 1, 0
        };
    }

    static Matrix2D Rotation(float rad) {
        float c = std::cos(rad);
        float s = std::sin(rad);
        return { c, -s, 0,
                s,  c, 0 };
    }

    //// 平行移動行列を作る
    static Matrix2D Translation(const Location2D& t)
    {
        return { 1, 0, t.x_,
                0, 1, t.y_ };
    }

    static Matrix2D Multiply(const Matrix2D& a, const Matrix2D& b)
    {
        return {
            a.m00 * b.m00 + a.m01 * b.m10,
            a.m00 * b.m01 + a.m01 * b.m11,
            a.m00 * b.tx + a.m01 * b.ty + a.tx,

            a.m10 * b.m00 + a.m11 * b.m10,
            a.m10 * b.m01 + a.m11 * b.m11,
            a.m10 * b.tx + a.m11 * b.ty + a.ty
        };
    }

    //// ---- 行列 × 点(ベクトル） ----

    //// 点（ベクトル）にアフィン変換を適用する
    //// 回転・平行移動をまとめて行う
    ////[m.m00 m.m01, m.tx][v.x]
    ////[m.m10 m.m11, m.ty][v.y] = ????
    ////[0,    0,     1   ][1  ]
    static Location2D TransformPoint(const Location2D& v, const Matrix2D& m)
    {
        Location2D result(0, 0);
        result.x_ = m.m00 * v.x_ + m.m01 * v.y_ + m.tx;
        result.y_ = m.m10 * v.x_ + m.m11 * v.y_ + m.ty;
        return result;
    }
};