#pragma once
#include "../Object/Base2DObject.h"
#include <DxLib.h>

namespace BulletParams {
    static const float SPEED = 600.0f;          // ë¨ìx
    static const unsigned int COLOR = GetColor(255, 255, 255); // îí
    static const float RADIUS = 2.0f;           // îºåa
    static const float LIFE = 3.0f;             // éıñΩÅiïbÅj
}

class Bullet : public Base2DObject {
private:
    float life_;
    unsigned int color_;
public:
    Bullet(const Location2D& loc, const Vector2D& vel, float radius, unsigned int color, float lifeTime);
    ~Bullet();
    void Update() override;
    void Draw() override;
};