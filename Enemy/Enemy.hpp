#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <list>
#include <vector>
#include <string>

#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"

class Bullet;
class PlayScene;

class Enemy : public Engine::Sprite {
protected:
	float speed;
	float hp;
	int money;
    float rotateRadian = 2 * ALLEGRO_PI;
	PlayScene* getPlayScene();
	virtual void OnExplode();
    float OriginalSpeed;
    float SlowDownTimeRemaining;
	float attackRotation;
    Engine::Point TargetPosition;
public:
	std::list<Sprite*> lockedPlayer;
	std::list<Bullet*> lockedBullets;
	Enemy(std::string img, float x, float y, float radius, float speed, float hp, int money);
 	void Hit(float damage);
	void Update(float deltaTime) override;
	void Draw() const override;
    void ApplySlowDown(float factor, float duration);
};
#endif // ENEMY_HPP
