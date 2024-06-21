#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Bullet/FourthBullet.hpp"
#include "Engine/Group.hpp"
#include "FourthTurret.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

const int FourthTurret::Price = 200;
FourthTurret::FourthTurret(float x, float y) :
    Turret("play/tower-base.png", "play/turret-7.png", x, y, 200, Price, 0.5) {
}
void FourthTurret::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new FourthBullet(Position + normalized * 36, diff, rotation, this));
    AudioHelper::PlayAudio("gun.wav");
}
