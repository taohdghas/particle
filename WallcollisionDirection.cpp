#include "WallcollisionDirection.h"

void WallcollisionDirection::Initialize() {
    particles_.clear(); 
}

void WallcollisionDirection::Update() {
    for (auto& particle : particles_) {
        particle.x += particle.speedX;
        particle.y += particle.speedY;

        particle.angle += particle.rotationSpeed;

        particle.lifetime--;

        particles_.erase(
            std::remove_if(particles_.begin(), particles_.end(), [](const Particle& p) {
                return p.lifetime <= 0;
                }), particles_.end());
    }
}
void WallcollisionDirection::Draw() {
    for (const auto& particle : particles_) {
        Novice::DrawBox(static_cast<int>(particle.x), static_cast<int>(particle.y),
            static_cast<int>(particle.w), static_cast<int>(particle.h),
            particle.angle, particle.color, kFillModeSolid);
    }
}
void WallcollisionDirection::OnCollision(float collisionX, float collisionY) {
    // 衝突位置を基準に生成
    const int numParticles = 70;  
    for (int i = 0; i < numParticles; ++i) {
        Particle particle;
        particle.x = collisionX;
        particle.y = collisionY;
        // パーティクルのサイズ
        particle.w = static_cast<float>(rand() % 20);
        particle.h = static_cast<float>(rand() % 20);
        // パーティクルの速度
        float angle = static_cast<float>((rand() % 360) * 3.14159265 / 180.0);
        float speed = static_cast<float>((rand() % 5 + 2));  
        particle.speedX = std::cos(angle) * speed;
        particle.speedY = std::sin(angle) * speed;
        // 回転速度
        particle.rotationSpeed = static_cast<float>((rand() % 10 - 5) / 10.0f);
        // パーティクルの描画時間
        particle.lifetime = 40 + (rand() % 30);
        particle.color = 0x76745b;
        particles_.push_back(particle);
    }
}
