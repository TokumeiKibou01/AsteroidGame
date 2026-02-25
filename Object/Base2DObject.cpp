#include "BaseObject.h"
#include "Base2DObject.h"
#include "../Library/Location2D.h"
#include "../Library/Vector2D.h"

Base2DObject::Base2DObject(const std::string& name, const Location2D& location, const Vector2D& vector, const Vector2D& dir, 
                            float radius, float omega, const bool& isAlive)
    : BaseObject(name, isAlive){
    name_ = name;
    location_ = location;
    vector_ = vector;
    direction_ = dir;
    radius_ = radius;
    omega_ = omega;
    angle_ = 0.0f;
}

Base2DObject::Base2DObject(const std::string& name, const Location2D& location, const Vector2D& vector, bool isAlive)
    : Base2DObject(name, location, vector, Vector2D(), -1, -1, isAlive){
}

Base2DObject::~Base2DObject() {
}

bool Base2DObject::IsAABBCollation(const Location2D& loc) {
    int leftX = location_.x_, leftY = location_.y_;
    int rightX = location_.x_ + (radius_ + radius_), rightY = location_.y_ + (radius_ + radius_);
    if (loc.x_ > leftX && loc.y_ > leftY && loc.x_ < rightX && loc.y_ < rightY) { 
        return true;
    }

    return false;
}

bool Base2DObject::IsDistanceCollation(Base2DObject* obj) {
    float distance = location_.Distance(obj->GetLocation());
    if (distance < radius_ + obj->GetRadius()) {
        return true;
    }
    return false;
}
