#include "Vector2D.h"
#include <cmath>

Vector2D::Vector2D() {
    x_ = 0.0f;
    y_ = 0.0f;
}

Vector2D::Vector2D(float x, float y) {
    x_ = x;
    y_ = y;
}

float Vector2D::Length() {
    return sqrt(x_ * x_ + y_ + y_);
}

Vector2D Vector2D::Add(const Vector2D& other) {
    Vector2D result;
    result.x_ = x_ + other.x_;
    result.y_ = y_ + other.y_;
    return result;
}

Vector2D Vector2D::Subtract(const Vector2D& other) {
    Vector2D result;
    result.x_ = x_ - other.x_;
    result.y_ = y_ - other.y_;
    return result;
}

Vector2D Vector2D::Dot(const Vector2D& other) {
    Vector2D result;
    result.x_ = x_ * other.x_;
    result.y_ = y_ * other.y_;
    return result;
}

Vector2D Vector2D::Cross(const Vector2D& other) {
    Vector2D result;
    result.x_ = x_ * other.y_;
    result.y_ = y_ * other.x_;
    return result;
}

Vector2D Vector2D::Normalize() {
    float len = Length();
    return {
        x_ / len,
        y_ / len
    };
}

Vector2D Vector2D::operator+(const Vector2D& other) {
    return Add(other);
}

Vector2D Vector2D::operator-(const Vector2D& other) {
    return Subtract(other);
}

Vector2D Vector2D::operator*(int scalar) {
    return Vector2D(x_ * scalar, y_ * scalar);
}

Vector2D Vector2D::FromAngle(float angle) {
    return {
        cos(angle),
        sin(angle)
    };
}
