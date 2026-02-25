#pragma once
#include "../Object/Base2DObject.h"
#include <vector>

struct Particle {
    float alpha;
    Location2D offset_; //à íu
    Vector2D velocity; //ë¨ìx
    float life; //éıñΩ
    float radius; //îªíË
};

namespace ParticleParams {
    inline const Location2D GetOffSet() { return { 0.0f, 0.0f }; }
    inline const Vector2D GetVel() { return {0.0f, 0.0f}; }
    static const float SPEED[3] = { 50.0f, 100.0f, 150.0f };
    static const int LIFE = 3.0f;
    static const int RADIUS = 1.5f;
    static const int SIZE = 20;
    static const float DECAY = 0.95f; //å∏êäó¶
}

class ExplosionEffect : public Base2DObject {
private:
   std::vector<Particle> particles_;
public:
    ExplosionEffect(const Location2D& loc);
    ~ExplosionEffect();
    void Update() override;
    void Draw() override;
};

