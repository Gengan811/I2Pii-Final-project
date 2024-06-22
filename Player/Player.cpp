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
#include "Enemy/Enemy.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "UI/Animation/ExplosionEffect.hpp"
PlayScene* Player::getPlayScene() {
    return dynamic_cast<PlayScene*>(
        Engine::GameEngine::GetInstance().GetActiveScene());
}
Player::Player(std::string img,
               float x,
               float y,
               float w,
               float h,
               float anchorX,
               float anchorY,
               float rotation)
    : Image::Image(img, x, y, w, h, anchorX, anchorY) {
    hp = 30;
    atk = 20;
    Position.x = x;
    Position.y = y;
    Engine::LOG(Engine::INFO) << x << " " << y;
}

void Player::Hit(float damage) {
    hp -= damage;
    if (hp <= 0) {
        // Remove all turret's reference to target.
        // Remove all player's reference to enemy.
        for (auto& it : lockedEnemies)
            it->Target = nullptr;
        for (auto& it : lockedBullets)
            it->Target = nullptr;
        getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
        AudioHelper::PlayAudio("explosion.wav");
    }
}

void Player::Update(float deltaTime) {
    // Pre-calculate the velocity.
    Image::Update(deltaTime);
    PlayScene* scene = getPlayScene();
    // imgBase.Position = Position;
    // imgBase.Tint = Tint;
    // if (!Enabled)
    //     return;
    if (Target) {
        Engine::Point diff = Target->Position - Position;
        if (diff.Magnitude() > CollisionRadius) {
            Target->lockedPlayer.erase(lockedEnemyIterator);
            Target = nullptr;
            lockedEnemyIterator = std::list<Enemy *>::iterator()
        }
        if (!Target) {
            // Lock first seen target.
            // Can be improved by Spatial Hash, Quad Tree, ...
            // However, simply loop through all enemies is enough for this program.
            for (auto &it: scene->EnemyGroup->GetObjects()) {
                Engine::Point diff = it->Position - Position;
                if (diff.Magnitude() <= CollisionRadius) {
                    Target = dynamic_cast<Enemy *>(it);
                    Target->lockedPlayer.push_back(this);
                    lockedEnemyIterator = std::prev(Target->lockedPlayer.end());
                    break;
                }
            }
        }
        if (Target) {
            Engine::Point originRotation = Engine::Point(cos(Rotation - ALLEGRO_PI / 2),
                                                         sin(Rotation - ALLEGRO_PI / 2));
            Engine::Point targetRotation = (Target->Position - Position).Normalize();
            float maxRotateRadian = rotateRadian * deltaTime;
            float cosTheta = originRotation.Dot(targetRotation);
            // Might have floating-point precision error.
            if (cosTheta > 1) cosTheta = 1;
            else if (cosTheta < -1) cosTheta = -1;
            float radian = acos(cosTheta);
            Engine::Point rotation;
            if (abs(radian) <= maxRotateRadian)
                rotation = targetRotation;
            else
                rotation =
                        ((abs(radian) - maxRotateRadian) * originRotation + maxRotateRadian * targetRotation) / radian;
            // Add 90 degrees (PI/2 radian), since we assume the image is oriented upward.
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
}

void Player::OnKeyDown(int keyCode) {
    Engine::LOG(Engine::INFO) << "Key " << keyCode << " Down";
    if (keyCode == ALLEGRO_KEY_W) {
        Position.y--;
    } else if (keyCode == ALLEGRO_KEY_S) {
        Position.y++;
    } else if (keyCode == ALLEGRO_KEY_A) {
        Position.x--;
    } else if (keyCode == ALLEGRO_KEY_D) {
        Position.x++;
    }
}

void Player::Draw() const {
    al_draw_tinted_scaled_rotated_bitmap(
        bmp.get(), Tint, Anchor.x * GetBitmapWidth(),
        Anchor.y * GetBitmapHeight(), Position.x, Position.y,
        Size.x / GetBitmapWidth(), Size.y / GetBitmapHeight(), Rotation, 0);

    if (PlayScene::DebugMode) {
        // Draw collision radius.
        al_draw_circle(Position.x, Position.y, CollisionRadius,
                       al_map_rgb(255, 0, 0), 2);
    }
}
