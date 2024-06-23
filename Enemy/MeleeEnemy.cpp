#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <utility>

#include "Enemy/Enemy.hpp"
#include "Engine/Collider.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "MeleeEnemy.hpp"
#include "Scene/PlayScene.hpp"
#include "Player/Player.hpp"

PlayScene* MeleeEnemy::getPlayScene() {
    return dynamic_cast<PlayScene*>(
        Engine::GameEngine::GetInstance().GetActiveScene());
}
MeleeEnemy::MeleeEnemy(std::string imgBase,
                       float x,
                       float y,
                       float radius,
                       float speed,
                       float cooldown,
                       float hp,
                       int attack,
                       int money)
    : Enemy(imgBase, x, y, radius, speed, hp, money),
      attack(attack),
      coolDown(cooldown) {
    reload = cooldown;
    CollisionRadius = radius;
}

void MeleeEnemy::Update(float deltaTime) {
    Enemy::Update(deltaTime);
    PlayScene* scene = getPlayScene();
    if (Engine::Collider::IsCircleOverlap(
            getPlayScene()->player->Position,
            getPlayScene()->player->CollisionRadius, Position,
            CollisionRadius)) {
        reload -= deltaTime;
        if (reload <= 0) {
            reload = coolDown;
            getPlayScene()->player->Hit(attack);
        }
    }
}

void MeleeEnemy::Draw() const {
    Enemy::Draw();
}