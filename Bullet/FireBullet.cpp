#include <allegro5/base.h>
#include <random>
#include <string>


#include "Enemy/Enemy.hpp"
#include "FireBullet.hpp"
#include "Engine/Group.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/GameEngine.hpp"

class Turret;

FireBullet::FireBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Sprite* parent) :
	Bullet("play/bullet/bullet-1.png", 500, 1, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
	// TODO: [CUSTOM-TOOL] You can imitate the 2 files: 'FireBullet.hpp', 'FireBullet.cpp' to create a new bullet.
}

void FireBullet::Update(float deltaTime) {
    Bullet::Update(deltaTime);
}

void FireBullet::OnExplode(Enemy* enemy) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(2, 5);
}

