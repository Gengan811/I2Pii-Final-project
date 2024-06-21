#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_FOURTHBULLET_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_FOURTHBULLET_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
    struct Point;
}  // namespace Engine

class FourthBullet : public Bullet {
public:
    explicit FourthBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
    void OnExplode(Enemy* enemy) override;
};
#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_FOURTHBULLET_HPP
