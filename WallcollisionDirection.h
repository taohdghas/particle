#pragma once
#include "Novice.h"
class WallcollisionDirection
{
public:
	void Initialize();

	void Update();

	void Draw();

	// 衝突エフェクトを開始
	void StartEffect(const Vector3& collisionPoint);
private:

};

