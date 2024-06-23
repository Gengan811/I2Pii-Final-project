#ifndef SAMPLEENEMY_HPP
#define SAMPLEENEMY_HPP
#include "MeleeEnemy.hpp"
#include "Player/RangedPlayer.hpp"


class SampleEnemy : public MeleeEnemy {
   public:
    SampleEnemy(int x, int y);
    void Update(float deltaTime) override;
    void Draw() const override;
};
#endif  // SAMPLEENEMY_HPP
