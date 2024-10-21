#pragma once
#include "Novice.h"
#include <vector>
#include <cstdlib>
#include <cmath>

struct Particle {
    float x, y;      
    float w, h;     
    float angle;     //回転角度
    float speedX, speedY;  //移動速度
    float rotationSpeed;   //回転速度
    int lifetime;    //描画時間
    unsigned int color;
};

class WallcollisionDirection
{
public:
    void Initialize();
    void Update();
    void Draw();
    void OnCollision(float collisionX, float collisionY);

private:
    std::vector<Particle> particles_; 
};