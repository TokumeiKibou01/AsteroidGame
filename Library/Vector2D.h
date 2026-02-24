#pragma once
class Vector2D {
private:
public:
    float x_;
    float y_;

    Vector2D();
    Vector2D(float x, float y);

    float Length();

    Vector2D Add(const Vector2D& other);
    Vector2D Subtract(const Vector2D& other);
    Vector2D Dot(const Vector2D& other);
    Vector2D Cross(const Vector2D& other);
    Vector2D Normalize();

    /// <summary>
    /// 加算する関数（Addと同じ）
    /// </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    Vector2D operator+(const Vector2D& other);

    /// <summary>
    /// 減算する関数（Subtractと同じ）
    /// </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    Vector2D operator-(const Vector2D& other);

    Vector2D operator*(int scalar);

    /// <summary>
    /// 角度から単位ベクトルを作る
    /// </summary>
    /// <param name="angle"></param>
    /// <returns></returns>
    static Vector2D FromAngle(float angle);
    
};

