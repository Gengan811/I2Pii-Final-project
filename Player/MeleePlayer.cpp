#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <utility>

#include "Enemy/Enemy.hpp"
#include "Engine/Collider.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "MeleePlayer.hpp"
#include "Player.hpp"
#include "Scene/PlayScene.hpp"

PlayScene* MeleePlayer::getPlayScene() {
    return dynamic_cast<PlayScene*>(
        Engine::GameEngine::GetInstance().GetActiveScene());
}
MeleePlayer::MeleePlayer(std::string imgBase,
                         float x,
                         float y,
                         float radius,
                         float speed,
                         float cooldown,
                         float hp,
                         int attack,
                         int money)
    : Player(imgBase, x, y, radius, speed, hp),
      attack(attack),
      coolDown(cooldown) {
    reload = cooldown;
    CollisionRadius = radius;
}

void MeleePlayer::Update(float deltaTime) {
    Player::Update(deltaTime);
    PlayScene* scene = getPlayScene();

    Enemy* enemy_it;

    for (auto& it : scene->EnemyGroup->GetObjects()) {
        enemy_it = (Enemy*)it;
        if (Engine::Collider::IsCircleOverlap(enemy_it->Position, enemy_it->CollisionRadius,
                                              Position, CollisionRadius)) {
            reload -= deltaTime;
            if (reload <= 0) {
                reload = coolDown;
                enemy_it->Hit(attack);
            }
        }
    }
}

void MeleePlayer::Draw() const {
    Player::Draw();
}