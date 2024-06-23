#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <utility>

#include "Enemy/Enemy.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IObject.hpp"
#include "Engine/IScene.hpp"
#include "Engine/LOG.hpp"
#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"
#include "RangedPlayer.hpp"
#include "Scene/PlayScene.hpp"

PlayScene* RangedPlayer::getPlayScene() {
    return dynamic_cast<PlayScene*>(
        Engine::GameEngine::GetInstance().GetActiveScene());
}
RangedPlayer::RangedPlayer(std::string imgBase,
                           std::string imgBullet,
                           float x,
                           float y,
                           float radius,
                           float speed,
                           float cooldown,
                           float hp)
    : Player(imgBase, x, y, radius, speed, hp), coolDown(cooldown) {
    reload = cooldown;
    CollisionRadius = radius;
}

void RangedPlayer::Update(float deltaTime) {
    Player::Update(deltaTime);
    PlayScene* scene = getPlayScene();
    // Engine::LOG(Engine::INFO) << Target;
    if (!Target) {
        Target = dynamic_cast<Enemy*>(scene->EnemyGroup->GetObjects().back());
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

void RangedPlayer::Draw() const {
    Player::Draw();
}