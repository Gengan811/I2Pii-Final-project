#ifndef RANGEDPLAYER_HPP
#define RANGEDPLAYER_HPP
#include <allegro5/base.h>
#include <list>
#include <string>

#include "Bullet/Bullet.hpp"
#include "Player/Player.hpp"

class PlayScene;

class RangedPlayer : public Player {
protected:
    float coolDown;
    float reload = 0;
    std::list<Sprite*>::iterator lockedTurretIterator;
    PlayScene* getPlayScene();
    // Reference: Design Patterns - Factory Method.
    virtual void CreateBullet() = 0;

public:
    RangedPlayer(std::string imgBase,
                 std::string imgBullet,
                 float x,
                 float y,
                 float radius,
                 float speed,
                 float cooldown,
                 float hp);
    void Update(float deltaTime) override;
    void Draw() const override;
};
#endif  // RANGEDPLAYER_HPP