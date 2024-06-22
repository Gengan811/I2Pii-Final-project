//
// Created by user on 2024/5/26.
//

#ifndef COIN_H
#define COIN_H
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
    struct Point;
}  // namespace Engine

class Coin: public Bullet {
public:
    explicit Coin(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
    void OnExplode(Enemy* enemy) override;
    void Update(float deltaTime) override;
};
#endif

