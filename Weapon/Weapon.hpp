//
// Created by 胡耿安 on 2024/6/21.
//

#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_WEAPON_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_WEAPON_HPP
#include <allegro5/base.h>
#include <list>
#include <string>

#include "Engine/Sprite.hpp"

class Enemy;
class Player;
class PlayScene;

class Weapon: public Engine::Sprite {
protected:
    int price;
    float coolDown;
    float reload = 0;
    Sprite imgBase;
    PlayScene* getPlayScene();
    virtual void CreateBullet() = 0;
    // float rotateRadian = 2 * ALLEGRO_PI;
    // std::list<Weapon*>::iterator lockedTurretIterator;

public:
    bool Enabled = true;
    bool Preview = false;
    Enemy* Target = nullptr;
    Weapon(std::string imgBase, std::string imgTurret, float x, float y, float radius, float coolDown);
    void Update(float deltaTime) override;
    void Draw() const override;
    // int GetPrice() const;
};
#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_WEAPON_HPP
