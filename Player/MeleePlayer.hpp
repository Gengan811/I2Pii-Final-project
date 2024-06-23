#ifndef MELEEPLAYER_HPP
#define MELEEPLAYER_HPP
#include <allegro5/base.h>
#include <list>
#include <string>

#include "Bullet/Bullet.hpp"
#include "Player/Player.hpp"

class PlayScene;

class MeleePlayer : public Player {
   protected:
    float coolDown = 10;
    float reload = 0;
    int attack;
    std::list<Sprite*>::iterator lockedTurretIterator;
    PlayScene* getPlayScene();

   public:
    MeleePlayer(std::string imgBase,
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
#endif  // MELEEPLAYER_HPP
