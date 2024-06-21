//
// Created by 胡耿安 on 2024/6/21.
//

#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_PLAYER_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_PLAYER_HPP
#include <list>
#include <vector>
#include <string>

#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"

class Bullet;
class PlayScene;
class Turret;

class Player : public Engine::Sprite {
protected:
    std::vector<Engine::Point> path;
    float speed;
    float hp;
    int money;
    PlayScene* getPlayScene();
    virtual void OnExplode();
public:
    float reachEndTime;
    std::list<Turret*> lockedTurrets;
    std::list<Bullet*> lockedBullets;
    Player(std::string img, float x, float y, float radius, float speed, float hp, int money);
    void Hit(float damage);
    void UpdatePath(const std::vector<std::vector<int>>& mapDistance);
    void Update(float deltaTime) override;
    void Draw() const override;
};
#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_PLAYER_HPP