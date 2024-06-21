#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_FOURTHTURRET_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_FOURTHTURRET_HPP
#include "Turret.hpp"

class FourthTurret: public Turret {
public:
    static const int Price;
    FourthTurret(float x, float y);
    void CreateBullet() override;
};
#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_FOURTHTURRET_HPP
