#include <string>

#include "Bullet/FireBullet.hpp"
#include "Engine/AudioHelper.hpp"
#include "MeleeEnemy.hpp"
#include "SampleEnemy.hpp"
#include "Scene/PlayScene.hpp"  // Include the header file for PlayScene

SampleEnemy::SampleEnemy(int x, int y)
    : MeleeEnemy("play/enemy-1.png", x, y, 50, 50, 5, 100, 5000, 5) {}

void SampleEnemy::Update(float deltaTime) {
    MeleeEnemy::Update(deltaTime);
}
void SampleEnemy::Draw() const {
    MeleeEnemy::Draw();
}
