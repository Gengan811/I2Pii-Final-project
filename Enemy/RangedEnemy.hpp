#ifndef RANGEDSPRITE_HPP
#define RANGEDSPRITE_HPP
#include <allegro5/base.h>
#include <list>
#include <string>

#include "Bullet/Bullet.hpp"
#include "Enemy/Enemy.hpp"

class Enemy;
class PlayScene;

class RangedEnemy : public Enemy {
   protected:
    float coolDown = 10;
    float reload = 0;
    std::list<Sprite*>::iterator lockedTurretIterator;
    PlayScene* getPlayScene();
    // Reference: Design Patterns - Factory Method.
    virtual void CreateBullet() = 0;

   public:
    RangedEnemy(std::string imgBase,
                std::string imgTurret,
                float x,
                float y,
                float radius,
                float speed,
                float cooldown,
                float hp,
                int money);
    void Update(float deltaTime) override;
    void Draw() const override;
};
#endif  // RANGEDSPRITE_HPP
