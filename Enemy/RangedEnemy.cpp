#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <utility>

#include "Enemy/Enemy.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IObject.hpp"
#include "Engine/IScene.hpp"
#include "Engine/Point.hpp"
#include "RangedEnemy.hpp"
#include "Scene/PlayScene.hpp"

PlayScene* RangedEnemy::getPlayScene() {
    return dynamic_cast<PlayScene*>(
        Engine::GameEngine::GetInstance().GetActiveScene());
}
RangedEnemy::RangedEnemy(std::string imgBase,
                         std::string imgBullet,
                         float x,
                         float y,
                         float radius,
                         float speed,
                         float cooldown,
                         float hp,
                         int money)
    : Enemy(imgBase, x, y, radius, speed, hp, money), coolDown(cooldown) {
    CollisionRadius = radius;
}

void RangedEnemy::Update(float deltaTime) {
    Enemy::Update(deltaTime);
    PlayScene* scene = getPlayScene();
    if (Target) {
        reload -= deltaTime;
        if (reload <= 0) {
            reload = coolDown;
            CreateBullet();
        }
    }
}

void RangedEnemy::Draw() const {
    Enemy::Draw();
}