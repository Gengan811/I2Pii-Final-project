//
// Created by 胡耿安 on 2024/6/23.
//

#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_BOSS_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_BOSS_HPP
#include "RangedEnemy.hpp"
#include "Player/RangedPlayer.hpp"
class Boss : public RangedEnemy {
public:
    Boss(std::string imgBase,
        std::string imgBullet,
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
    void CreateBullet() override;
};
#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_BOSS_HPP
