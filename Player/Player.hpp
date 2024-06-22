//
// Created by 胡耿安 on 2024/6/21.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <list>
#include <string>
#include <vector>

#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"
#include "Engine/IControl.hpp"
#include "Enemy/Enemy.hpp"

class Bullet;
class PlayScene;
class Enemy;

class Player : public Engine::Image, public Engine::IControl {
   protected:
    std::vector<Engine::Point> path;
    float hp;
    float atk;
    float Rotation;
    float coolDown;
    float reload = 0;
    float rotateRadian = 2 * ALLEGRO_PI;
    std::list<Enemy*>::iterator lockedEnemyIterator;
    // Color tint.
    ALLEGRO_COLOR Tint;
    // Assume a circle is a good approximation of the sprite's boundary.
    float CollisionRadius = 0;
    PlayScene* getPlayScene();

   public:
    std::list<Enemy*> lockedEnemies;
    std::list<Bullet*> lockedBullets;
    Enemy* Target = nullptr;
    explicit Player(std::string img,
                    float x,
                    float y,
                    float w = 0,
                    float h = 0,
                    float anchorX = 0.5f,
                    float anchorY = 0.5f,
                    float rotation = 0);

    void Hit(float damage);
    void Update(float deltaTime) override;
    void Draw() const override;
    void OnKeyDown(int keyCode) override;
    virtual void CreateBullet();
};
#endif  // PLAYER_HPP