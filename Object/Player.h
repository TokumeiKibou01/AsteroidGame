#pragma once
#include "Base2DObject.h"
#include "../Library/Location2D.h"

class Player : public Base2DObject {
private:
    Location2D vertex_[3]; //3äpå`ÇÃí∏ì_ç¿ïW
public:
    Player();
    Player(const Location2D& loc, const Vector2D& vel, const Vector2D& dir, float radius, float omega);
    ~Player();
    void Update() override;
    void Draw() override;
};