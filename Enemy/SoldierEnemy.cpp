#include <string>

#include "Bullet/FireBullet.hpp"
#include "Enemy.hpp"
#include "Engine/AudioHelper.hpp"
#include "Scene/PlayScene.hpp"  // Include the header file for PlayScene
#include "SoldierEnemy.hpp"

SoldierEnemy::SoldierEnemy(int x, int y)
    : RangedEnemy("play/enemy-1.png",
                  "play/bullet-1.png",
                  x,
                  y,
                  50,
                  50,
                  1,
                  100,
                  5) {}

void SoldierEnemy::Update(float deltaTime) {
    RangedEnemy::Update(deltaTime);
}
void SoldierEnemy::Draw() const {
    RangedEnemy::Draw();
}
void SoldierEnemy::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2),
                                       sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    // Change bullet position to the front of the gun barrel.
    Enemy::getPlayScene()->BulletGroup->AddNewObject(
        new FireBullet(Position + normalized * 36, diff, rotation, this));
    AudioHelper::PlayAudio("gun.wav");
}
