#ifndef MELEEENEMY_HPP
#define MELEEENEMY_HPP
#include <allegro5/base.h>
#include <list>
#include <string>

#include "Bullet/Bullet.hpp"
#include "Enemy/Enemy.hpp"

class Enemy;
class PlayScene;

class MeleeEnemy : public Enemy {
   protected:
    float coolDown = 10;
    float reload = 0;
    int attack;
    std::list<Sprite*>::iterator lockedTurretIterator;
    PlayScene* getPlayScene();
    // Reference: Design Patterns - Factory Method.
    virtual void CreateBullet() = 0;

   public:
    MeleeEnemy(std::string imgBase,
               float x,
               float y,
               float radius,
               float speed,
               float cooldown,
               float hp,
               int attack,
               int money);
    void Update(float deltaTime) override;
    void Draw() const override;
};
#endif  // MELEEENEMY_HPP
