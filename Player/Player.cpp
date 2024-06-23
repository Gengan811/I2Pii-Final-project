//
// Created by 胡耿安 on 2024/6/21.
//

#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <random>
#include <string>
#include <vector>

#include "Bullet/Bullet.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"
#include "Engine/LOG.hpp"
#include "Player.hpp"
#include "Scene/PlayScene.hpp"

#include "UI/Animation/ExplosionEffect.hpp"

PlayScene* Player::getPlayScene() {
    return dynamic_cast<PlayScene*>(
        Engine::GameEngine::GetInstance().GetActiveScene());
}
Player::Player(std::string img,
               float x,
               float y,
               float radius,
               float speed,
               float hp)
    : Sprite(img, x, y, radius * 2, radius * 2), speed(speed), hp(hp) {
    hp = 30;
    atk = 20;
    Position.x = x;
    Position.y = y;
    CollisionRadius = radius;
    TargetPosition = Position;
    is_moving = false;
}

void Player::Hit(float damage) {
    hp -= damage;
    if (hp <= 0) {
        Engine::GameEngine::GetInstance().ChangeScene("lose-scene");
    }
}

void Player::Update(float deltaTime) {
    if (is_moving) {
        if ((TargetPosition - Position).Magnitude() < speed * deltaTime) {
            is_moving = false;
            Position = TargetPosition;
            Velocity = Engine::Point(0, 0);
            getPlayScene()->CalculateBFSDistance();
        }
        Sprite::Update(deltaTime);
    }
}

void Player::OnKeyDown(int keyCode) {
    if (is_moving)
        return;
    if (keyCode == ALLEGRO_KEY_W) {
        if (getPlayScene()->CheckPixelValid(
                Position.x, Position.y - PlayScene::BlockSize)) {
            Velocity = Engine::Point(0, -speed);
            TargetPosition =
                Engine::Point(Position.x, Position.y - PlayScene::BlockSize);
            is_moving = true;
        }
    } else if (keyCode == ALLEGRO_KEY_S) {
        if (getPlayScene()->CheckPixelValid(
                Position.x, Position.y + PlayScene::BlockSize)) {
            Velocity = Engine::Point(0, speed);
            TargetPosition =
                Engine::Point(Position.x, Position.y + PlayScene::BlockSize);
            is_moving = true;
        }
    } else if (keyCode == ALLEGRO_KEY_A) {
        if (getPlayScene()->CheckPixelValid(Position.x - PlayScene::BlockSize,
                                            Position.y)) {
            Velocity = Engine::Point(-speed, 0);
            TargetPosition =
                Engine::Point(Position.x - PlayScene::BlockSize, Position.y);
            is_moving = true;
        }
    } else if (keyCode == ALLEGRO_KEY_D) {
        if (getPlayScene()->CheckPixelValid(Position.x - PlayScene::BlockSize,
                                            Position.y)) {
            Velocity = Engine::Point(speed, 0);
            TargetPosition =
                Engine::Point(Position.x + PlayScene::BlockSize, Position.y);
            is_moving = true;
        }
    }
}

void Player::Draw() const {
    Sprite::Draw();

    if (PlayScene::DebugMode) {
        // Draw collision radius.
        al_draw_circle(Position.x, Position.y, CollisionRadius,
                       al_map_rgb(255, 0, 0), 2);
    }
}
