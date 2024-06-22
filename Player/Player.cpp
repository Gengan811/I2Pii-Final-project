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
#include "Turret/Turret.hpp"
#include "UI/Animation/DirtyEffect.hpp"
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
               float hp,
               int money)
    : Engine::Image(img, x, y), hp(hp) {
    CollisionRadius = radius;
}
void Player::Hit(float damage) {
    hp -= damage;
    if (hp <= 0) {
        // Remove all turret's reference to target.
        // Remove all enemy's reference to target.
        for (auto& it : lockedTurrets)
            it->Target = nullptr;
        for (auto& it : lockedBullets)
            it->Target = nullptr;
        getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
        AudioHelper::PlayAudio("explosion.wav");
    }
}

void Player::Update(float deltaTime) {
    // Pre-calculate the velocity.
    Sprite::Update(deltaTime);
}

void Player::OnKeyDown() {
    if (keyCode == ALLEGRO_KEY_W) {
        y--;
    } else if (keyCode == ALLEGRO_KEY_S) {
        y++;
    } else if (keyCode == ALLEGRO_KEY_A) {
        x--;
    } else if (keyCode == ALLEGRO_KEY_D) {
        x++;
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
