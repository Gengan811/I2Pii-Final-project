//
// Created by 胡耿安 on 2024/6/21.
//

#ifndef WOLF_HPP
#define WOLF_HPP
#include "RangedPlayer.hpp"

class Wolf : public RangedPlayer {
public:
    Wolf(int x, int y);
    void CreateBullet() override;
    void Update(float deltaTime) override;
    void Draw() const override;
};
#endif //WOLF_HPP
