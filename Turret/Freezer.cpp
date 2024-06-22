#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Bullet/Ice.hpp"
#include "Engine/Group.hpp"
#include "Freezer.h"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"
const int Freezer::Price = 150;
Freezer::Freezer(float x, float y) :
    Turret("play/tower-base.png", "play/turret-7.png", x, y, 200, Price, 5) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}
void Freezer::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new Ice(Position + normalized * 36, diff, rotation, this));
    AudioHelper::PlayAudio("fire.wav");
}
