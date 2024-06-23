#ifndef SOLDIERENEMY_HPP
#define SOLDIERENEMY_HPP
#include "RangedEnemy.hpp"
#include "Player/RangedPlayer.hpp"


class SoldierEnemy : public RangedEnemy {
   public:
    SoldierEnemy(int x, int y);
    void Update(float deltaTime) override;
    void Draw() const override;
    void CreateBullet() override;
};
#endif  // SOLDIERENEMY_HPP
