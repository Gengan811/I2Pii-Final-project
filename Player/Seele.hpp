//
// Created by 胡耿安 on 2024/6/21.
//

#ifndef SEELE_HPP
#define SEELE_HPP
#include "MeleePlayer.hpp"

class Seele : public MeleePlayer {
public:
    Seele(int x, int y);
    void Update(float deltaTime) override;
    void Draw() const override;
};
#endif //SEELE_HPP
