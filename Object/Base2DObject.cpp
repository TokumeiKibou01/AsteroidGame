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