#include "ExplosionEffect.h"
#include <DxLib.h>
#include "../Library/MathUtil.h"

ExplosionEffect::ExplosionEffect(const Location2D& loc)
    : Base2DObject("ExplosionEffect", loc, Vector2D(), Vector2D(), -1, -1, true) {
    particles_.clear();

    Particle particle;
    particle.offset_ = ParticleParams::GetOffSet();
    particle.velocity = ParticleParams::GetVel();
    particle.life = ParticleParams::LIFE; //Žõ–½3•b
    particle.radius = ParticleParams::RADIUS; //”¼Œa5

    //’Ç‰Á‚·‚é
    //particles_[0] = p;
    for (int n = 0; n < ParticleParams::SIZE; n++) {
        float random = (float)GetRand(360) * (MathUtil::PI_F / 180.0f);
        Vector2D direction = MathUtil::FromAngle((float)random);
        particle.velocity = direction * ParticleParams::SPEED[GetRand(2)];

        particles_.push_back(particle);
    }
}

ExplosionEffect::~ExplosionEffect()
{
}

void ExplosionEffect::Update() {
    float dt = GetDeltaTime();
    bool allDead = true;

    for (auto& particle : particles_) {
        if (particle.life > 0.0f) {
            allDead = false;
            particle.offset_ = particle.offset_ + (particle.velocity * dt); // offset + (vel*dt);
            float ratio = 1.0f - particle.life / ParticleParams::LIFE;
            // particle.velocity = Math2D::Mul(particle.velocity, 1.0 - EaseFunc["InOutQuart"](ratio));
            particle.velocity = particle.velocity * (1.0f - MathUtil::Lerp::easeInOutQuart(ratio));
            particle.life -= dt;
        }
        if (particle.life < 0.0f) {
            particle.life = 0.0f;
        }

        float lifeRatio = 1.0f - particle.life / ParticleParams::LIFE;
        // particle.alpha = 1.0f - EaseFunc["InExpo"](lifeRatio);
        particle.alpha = MathUtil::Lerp::Lerp<float>(1.0f, 0.0f, lifeRatio, MathUtil::Lerp::easeInExpo);
    }

    if (allDead) {
        isAlive_ = false;
    }
}

void ExplosionEffect::Draw() {
    if (!isAlive_) return;

    for (auto& particle : particles_) {
        if (particle.life > 0.0f) {
            Location2D drawPos = GetLocation() + particle.offset_;
            Location2D screenPos = MathUtil::WorldToScreen(drawPos);
            DrawCircle((int) screenPos.x_, (int) screenPos.y_, particle.radius, GetColor(255, 0, 0));
            unsigned int particleColor = GetColor(
            	(int)(255 * particle.alpha),
            	(int)(255 * particle.alpha),
            	(int)(255 * particle.alpha)
            );

            DrawCircleAA((int)screenPos.x_, (int)screenPos.y_, particle.radius, 60,
                particleColor);
        }
    }
}
