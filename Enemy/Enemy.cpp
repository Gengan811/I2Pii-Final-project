#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <random>
#include <string>
#include <vector>

#include "Bullet/Bullet.hpp"
#include "Enemy/Enemy.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"
#include "Engine/LOG.hpp"
#include "Scene/PlayScene.hpp"
#include "Turret/Turret.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "UI/Animation/ExplosionEffect.hpp"

PlayScene* Enemy::getPlayScene() {
    return dynamic_cast<PlayScene*>(
        Engine::GameEngine::GetInstance().GetActiveScene());
}
void Enemy::OnExplode() {
    getPlayScene()->EffectGroup->AddNewObject(
        new ExplosionEffect(Position.x, Position.y));
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distId(1, 3);
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 20);
    for (int i = 0; i < 10; i++) {
        // Random add 10 dirty effects.
        getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect(
            "play/dirty-" + std::to_string(distId(rng)) + ".png", dist(rng),
            Position.x, Position.y));
    }
}
Enemy::Enemy(std::string img,
             float x,
             float y,
             float radius,
             float speed,
             float hp,
             int money)
    : Engine::Sprite(img, x, y), speed(speed), hp(hp), money(money) {
    CollisionRadius = radius;
    OriginalSpeed = speed;
    SlowDownTimeRemaining = 0;
}
void Enemy::Hit(float damage) {
    hp -= damage;
    if (hp <= 0) {
        OnExplode();
        // Remove all turret's reference to target.
        for (auto& it : lockedPlayer)
            it->Target = nullptr;
        for (auto& it : lockedBullets)
            it->Target = nullptr;
        getPlayScene()->EarnMoney(money);
        getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
        AudioHelper::PlayAudio("explosion.wav");
    }
}

void Enemy::ApplySlowDown(float factor, float duration) {
    if (SlowDownTimeRemaining > 0)
        return;
    speed *= factor;
    SlowDownTimeRemaining = duration;
}

Engine::Point findNextStep(PlayScene* scene,
                           int start_x,
                           int start_y,
                           int num) {
    for (auto& dir : PlayScene::directions) {
        int x = start_x + dir.x;
        int y = start_y + dir.y;
        if (x < 0 || x >= PlayScene::MapWidth || y < 0 ||
            y >= PlayScene::MapHeight || scene->mapDistance[y][x] != num - 1)
            continue;
        return Engine::Point(x, y);
    }
}

void Enemy::Update(float deltaTime) {
    if (SlowDownTimeRemaining > 0) {
        SlowDownTimeRemaining -= deltaTime;
        if (SlowDownTimeRemaining <= 0) {
            speed = OriginalSpeed;
        }
    }

    // Pre-calculate the velocity.
    int x = static_cast<int>(floor(Position.x / PlayScene::BlockSize));
    int y = static_cast<int>(floor(Position.y / PlayScene::BlockSize));
    Engine::Point pos(x, y);
    float remainSpeed = speed * deltaTime;
    while (remainSpeed != 0) {
        Engine::Point target = findNextStep(getPlayScene(), x, y,
                                            getPlayScene()->mapDistance[y][x]);
        if (target == pos) {
            break;
        }
        Engine::Point vec = target - Position;
        // Add up the distances:
        // 1. to path.back()
        // 2. path.back() to border
        // 3. All intermediate block size
        // 4. to end point
        Engine::Point normalized = vec.Normalize();
        if (remainSpeed - vec.Magnitude() > 0) {
            Position = target;
            remainSpeed -= vec.Magnitude();
        } else {
            Velocity = normalized * remainSpeed / deltaTime;
            remainSpeed = 0;
        }
    }
    Rotation = atan2(Velocity.y, Velocity.x);
    Sprite::Update(deltaTime);
}
void Enemy::Draw() const {
    Sprite::Draw();
    if (PlayScene::DebugMode) {
        // Draw collision radius.
        al_draw_circle(Position.x, Position.y, 200,
                       al_map_rgb(255, 0, 0), 2);
    }
}
