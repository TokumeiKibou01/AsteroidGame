#include "Location2D.h"
#include <cmath>
#include "Vector2D.h"

Location2D::Location2D() {
    x_ = 0.0f;
    y_ = 0.0f;
}

Location2D::Location2D(float x, float y) {
    x_ = x;
    y_ = y;
}

float Location2D::Distance(const Location2D& otherLoc) {
    return sqrt((x_ - otherLoc.x_) * (x_ - otherLoc.x_) +
                (y_ - otherLoc.y_) * (y_ - otherLoc.y_));
}

Location2D Location2D::operator+(const Location2D& otherLoc) {
    Location2D result = Location2D(x_ + otherLoc.x_, y_ + otherLoc.y_);
    return result;
}

Location2D Location2D::operator+(const Vector2D& otherLoc) {
    Location2D result = Location2D(x_ + otherLoc.x_, y_ + otherLoc.y_);
    return result;
}

Location2D Location2D::operator-(const Location2D& otherLoc) {
    Location2D result = Location2D(x_ - otherLoc.x_, y_ - otherLoc.y_);
    return result;
}

Location2D Location2D::operator*(const float& scalar) {
    Location2D result = Location2D(x_ * scalar, y_ * scalar);
    return result;
}
