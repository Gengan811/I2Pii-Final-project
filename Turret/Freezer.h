//
// Created by user on 2024/5/25.
//

#ifndef Freezer_H
#define Freezer_H
#include "Turret.hpp"

class Freezer: public Turret {
public:
    static const int Price;
   Freezer(float x, float y);
    void CreateBullet() override;
};
#endif //Freezer_H
