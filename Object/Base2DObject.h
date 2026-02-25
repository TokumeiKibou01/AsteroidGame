#pragma once
#include <string>
#include "BaseObject.h"
#include "../Library/Location2D.h"
#include "../Library/Vector2D.h"

class Base2DObject : public BaseObject {
protected:
    Location2D location_; //ˆÊ’u
    Vector2D vector_; //‘¬‚³
    Vector2D direction_; //•ûŒü
    float radius_; //”¼Œa
    float omega_; //‰ñ“]‘¬“x
    float angle_; //‰ñ“]Šp
public:
    Base2DObject(const std::string& name, const Location2D& location, const Vector2D& vector, const Vector2D& dir,
                    float radius, float omega, const bool& isAlive);
    Base2DObject(const std::string& name, const Location2D& location, const Vector2D& vector, bool isAlive);
    ~Base2DObject();

    Location2D GetLocation() { return location_; };
    void SetLocation(const Location2D& loc) { location_ = loc; };
    Vector2D GetVector() { return vector_;  };
    void SetVector(const Vector2D& vec) { vector_ = vec; };
    Vector2D GetDirection() { return direction_; }
    void SetDirection(const Vector2D& dir) { direction_ = dir; }
    void SetRadius(float r) { radius_ = r; }
    float GetRadius() { return radius_; }
    void SetOmega(float omega) { omega_ = omega; };
    float GetOmega() { return omega_; }
    void SetAngle(float angle) { angle_ = angle; }
    float GetAngle() { return angle_; }

    virtual bool IsAABBCollation(const Location2D& loc);
    virtual bool IsDistanceCollation(Base2DObject* obj);
};

