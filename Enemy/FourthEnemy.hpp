#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_FOURTHENEMY_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_FOURTHENEMY_HPP
#include "Enemy.hpp"
#include "UI/Component/Label.hpp"

class FourthEnemy : public Enemy {
private:
    float healCooldown; // Time until the next heal.
    const float healInterval = 5.0f; // Heal every 5 seconds.
    const float healAmount = 10.0f; // Amount of HP to heal.
    const float maxHP = 20.0f; // Maximum HP value.
    float healDuration; // Duration of the healing effect.
    const float healingTime = 2.0f; // Time spent in healing state.
    bool isHealing; // Flag to check if the enemy is currently healing.

    Engine::Label* healingLabel; // Label for displaying healing text.
    float labelDuration; // Duration for which the label is displayed.
    const float labelDisplayTime = 3.0f; // Time for which the label is visible.

public:
    FourthEnemy(int x, int y);
    void Update(float deltaTime) override;
    void OnExplode() override; // Override OnExplode to handle label removal.
};
#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_FOURTHENEMY_HPP
