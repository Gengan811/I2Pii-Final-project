//
// Created by 胡耿安 on 2024/6/23.
//

#include "Boss.hpp"
#include <string>

#include "Bullet/FireBullet.hpp"
#include "Engine/AudioHelper.hpp"
#include "Scene/PlayScene.hpp"  // Include the header file for PlayScene
#include "Boss.hpp"
#include "Enemy.hpp"

Boss::Boss(std::string imgBase,
           std::string imgBullet,
           float x,
           float y,
           float radius,
           float speed,
           float cooldown,
           float hp,
           int attack,
           int money)
        : RangedEnemy(imgBase, imgBullet, x, y, radius, speed,cooldown, hp, money){
}

void Boss::Update(float deltaTime) {
    RangedEnemy::Update(deltaTime);
}
void Boss::Draw() const {
    RangedEnemy::Draw();
}
void Boss::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2),
                                       sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    Engine::Point normal = Engine::Point(-normalized.y, normalized.x);
    // Change bullet position to the front of the player.
    getPlayScene()->BulletGroup->AddNewObject(new FireBullet(
            Position + normalized * 36 - normal * 6, diff, rotation, this, false));
    AudioHelper::PlayAudio("gun.wav");
}

