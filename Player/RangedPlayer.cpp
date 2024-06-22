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
#include "Engine/Sprite.hpp"
#include "Engine/LOG.hpp"
#include "RangedPlayer.hpp"
#include "Scene/PlayScene.hpp"

PlayScene* RangedPlayer::getPlayScene() {
    return dynamic_cast<PlayScene*>(
        Engine::GameEngine::GetInstance().GetActiveScene());
}
RangedPlayer::RangedPlayer(std::string imgBase,
                           std::string imgTurret,
                           float x,
                           float y,
                           float radius,
                           float speed,
                           float cooldown,
                           float hp)
    : Player(imgBase, x, y, radius, speed, hp), coolDown(cooldown) {
    CollisionRadius = radius;
}

void RangedPlayer::Update(float deltaTime) {
    Player::Update(deltaTime);
    PlayScene* scene = getPlayScene();
    if (Target) {
        reload -= deltaTime;
        if (reload <= 0) {
            reload = coolDown;
            CreateBullet();
        }
    }
}

void RangedPlayer::Draw() const {
    Player::Draw();
}