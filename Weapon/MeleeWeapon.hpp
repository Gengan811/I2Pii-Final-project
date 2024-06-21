//
// Created by 胡耿安 on 2024/6/21.
//

#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_MELEEWEAPON_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_MELEEWEAPON_HPP
#include "Weapon.hpp"

class MeleeWeapon: public Weapon {
public:
    MeleeWeapon(float x, float y);
    void CreateBullet() override;
};
#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_MELEEWEAPON_HPP
