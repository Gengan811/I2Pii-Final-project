//
// Created by 胡耿安 on 2024/6/21.
//

#include "Wolf.hpp"
#include <allegro5/base.h>
#include <cmath>
#include <string>
#include "Bullet/FireBullet.hpp"
#include "Engine/LOG.hpp"

#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"
#include "Scene/PlayScene.hpp"

Wolf::Wolf(int x, int y)
    : RangedPlayer("character/wolf.png",
                   "play/bullet/bullet-1.png",
                   x,
                   y,
                   50,
                   200,
                   1,
                   500) {}

void Wolf::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2),
                                       sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    Engine::Point normal = Engine::Point(-normalized.y, normalized.x);
    // Change bullet position to the front of the player.
    getPlayScene()->BulletGroup->AddNewObject(new FireBullet(
        Position + normalized * 36 - normal * 6, diff, rotation, this, true));
    AudioHelper::PlayAudio("laser.wav");
}

void Wolf::Update(float deltaTime) {
    RangedPlayer::Update(deltaTime);
}

void Wolf::Draw() const {
    RangedPlayer::Draw();
}
