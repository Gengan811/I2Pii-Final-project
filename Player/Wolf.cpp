//
// Created by 胡耿安 on 2024/6/21.
//

#include "Wolf.hpp"
#include "Engine/LOG.hpp"

Wolf::Wolf(int x, int y)
    : RangedPlayer("character/wolf.png",
                   "play/bullet/bullet-1.png",
                   x,
                   y,
                   50,
                   200,
                   5,
                   500) {}
void Wolf::CreateBullet() {}
void Wolf::Update(float deltaTime) {
    RangedPlayer::Update(deltaTime);
}

void Wolf::Draw() const {
    RangedPlayer::Draw();
}
