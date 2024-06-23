//
// Created by 胡耿安 on 2024/6/21.
//

#include "Seele.hpp"
#include "Engine/LOG.hpp"

Seele::Seele(int x, int y)
    : MeleePlayer("character/seele.png", x, y, 50, 200, 5, 5, 500, 500) {}

void Seele::Update(float deltaTime) {
    MeleePlayer::Update(deltaTime);
}

void Seele::Draw() const {
    MeleePlayer::Draw();
}
