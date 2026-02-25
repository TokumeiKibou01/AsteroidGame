#pragma once
#include <cmath>
#include "Library/Location2D.h"
#include "MyDxLib.h"
#include "Matrix2D.h"

namespace MathUtil {

    const float PI_F = 3.14159265f;
    const double PI_D = 3.14159265358979323846;

    inline float ToRadian(float degree) {
        return(degree * (PI_F / 180.0f));
    }
    inline float ToDegree(float radian) {
        return(radian * (180.0f / PI_F));
    }

    inline Vector2D FromAngle(float rad) {
        return { cos(rad), sin(rad) };
    }

    inline Location2D TransformPoint(const Location2D& v, const Matrix2D& m)
    {
        Location2D res(0, 0);
        res.x_ = m.m00 * v.x_ + m.m01 * v.y_ + m.tx;
        res.y_ = m.m10 * v.x_ + m.m11 * v.y_ + m.ty;
        return res;
    }

    inline Location2D WorldToScreen(const Location2D& worldPos) {
        Location2D result;
        result.x_ = worldPos.x_;
        result.y_ = Screen::HEIGHT - worldPos.y_;
        return result;
    }

    namespace Lerp {
        inline float easeInOutSine(float x) {
            return -(cosf(x * PI_F) / 2);
        }

        inline float easeInExpo(float x) {
            return (x == 0.0f) ? 0.0f : powf(2.0f, 10.0f * (x - 1.0f));
        }

        inline float easeOutExpo(float x) {
            return (x == 1.0f) ? 1.0f : 1.0f - powf(2.0f, -10.0f * x);
        }

        inline float easeInOutQuart(float x) {
            return (x < 0.5f) ? 8.0f * x * x * x * x : 1.0f - powf(-2.0f * x + 2.0f, 4.0f) / 2.0f;
        }

        template <typename T>
        inline T Lerp(T start, T end, float rate, float (*easeFunc)(float) = nullptr) {
            if (easeFunc != nullptr) {
                rate = easeFunc(rate);
            }
            return (end - start) * rate + start;
        }
    }
}