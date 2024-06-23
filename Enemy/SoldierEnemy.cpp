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
                  10,
                  5) {}

void SoldierEnemy::Update(float deltaTime) {
    RangedEnemy::Update(deltaTime);
}
void SoldierEnemy::Draw() const {
    RangedEnemy::Draw();
}
void SoldierEnemy::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(attackRotation - ALLEGRO_PI / 2),
                                       sin(attackRotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    Engine::Point normal = Engine::Point(-normalized.y, normalized.x);
    // Change bullet position to the front of the player.
    getPlayScene()->BulletGroup->AddNewObject(new FireBullet(
        Position + normalized * 36 - normal * 6, diff, rotation, this, false));
    AudioHelper::PlayAudio("gun.wav");
}
