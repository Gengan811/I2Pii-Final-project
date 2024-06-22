//
// Created by user on 2024/5/26.
//

#ifndef GOLDFLOWER_H
#define GOLDFLOWER_H

#include "Turret.hpp"

class GoldFlower: public Turret {
public:
    static const int Price;
    GoldFlower(float x, float y);
    void CreateBullet() override;
};
#endif //GOLDFLOWER_H
