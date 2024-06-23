#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <utility>

#include "Enemy/Enemy.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IObject.hpp"
#include "Engine/LOG.hpp"
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
    reload = cooldown;
    CollisionRadius = radius;
}

void RangedEnemy::Update(float deltaTime) {
    Enemy::Update(deltaTime);
    PlayScene* scene = getPlayScene();
    // Engine::LOG(Engine::INFO) << Target;
    if (!Target) {
        Target = dynamic_cast<Player*>(scene->player);
    }
    if (Target) {
        Engine::Point originRotation = Engine::Point(
            cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
        Engine::Point targetRotation =
            (Target->Position - Position).Normalize();
        float maxRotateRadian = rotateRadian * deltaTime;
        float cosTheta = originRotation.Dot(targetRotation);
        // Might have floating-point precision error.
        if (cosTheta > 1)
            cosTheta = 1;
        else if (cosTheta < -1)
            cosTheta = -1;
        float radian = acos(cosTheta);
        Engine::Point rotation;
        if (abs(radian) <= maxRotateRadian)
            rotation = targetRotation;
        else
            rotation = ((abs(radian) - maxRotateRadian) * originRotation +
                        maxRotateRadian * targetRotation) /
                       radian;
        // Add 90 degrees (PI/2 radian), since we assume the image is oriented
        // upward.
        Rotation = atan2(rotation.y, rotation.x) + ALLEGRO_PI / 2;
        // Shoot reload.
        reload -= deltaTime;
        if (reload <= 0) {
            // shoot.
            reload = coolDown;
            CreateBullet();
        }
    }
}

void RangedEnemy::Draw() const {
    Enemy::Draw();
}