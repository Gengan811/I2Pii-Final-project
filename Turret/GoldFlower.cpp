#include <allegro5/base.h>
#include <cmath>
#include <string>
#include "Engine/AudioHelper.hpp"
#include "Bullet/Coin.h"
#include "Engine/Group.hpp"
#include "GoldFlower.h"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"
const int GoldFlower::Price = 25;
GoldFlower::GoldFlower(float x, float y) :
    Turret("play/Sunflower.png", "play/Transparent.png", x, y, 10000, Price, 10) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}
void GoldFlower::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(-ALLEGRO_PI / 2), sin( -ALLEGRO_PI / 2));
    float rotation = atan2(0, 0);
    Engine::Point normalized = diff.Normalize();
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new Coin(Position + normalized * 36, diff, rotation, this));
    AudioHelper::PlayAudio("Mario-coin-sound.wav");
}
