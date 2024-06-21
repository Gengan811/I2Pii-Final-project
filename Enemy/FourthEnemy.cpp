#include "FourthEnemy.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/LOG.hpp"
#include <functional>

#include "Engine/AudioHelper.hpp"
#include "UI/Component/Label.hpp"

FourthEnemy::FourthEnemy(int x, int y) : Enemy("play/enemy-4.png", x, y, 10, 50, 20, 8), healCooldown(healInterval), healDuration(0), isHealing(false), healingLabel(nullptr), labelDuration(0) {
}

void FourthEnemy::Update(float deltaTime) {
    // Call the base class update method to handle movement and other logic.
    Enemy::Update(deltaTime);

    if (isHealing) {
        // If currently healing, update the healing timer.
        healDuration -= deltaTime;
        if (healDuration <= 0) {
            // Healing is done, restore the original speed.
            speed = OriginalSpeed;
            isHealing = false;
        }
    } else {
        // Update the cooldown timer.
        healCooldown -= deltaTime;

        // If it's time to heal and health is not full, apply the healing.
        if (healCooldown <= 0 && hp < maxHP) {
            isHealing = true;
            healDuration = healingTime;
            speed /= 2; // Slow down during healing.
            hp += healAmount;
            // Ensure hp does not exceed a maximum value.
            hp = std::min(hp, maxHP);

            // Reset the heal cooldown timer.
            healCooldown = healInterval;

            // Display the healing text.
            healingLabel = new Engine::Label("Healing", "pirulen.ttf", 20, Position.x, Position.y - 20, 255, 0, 0, 255, 0.5, 0.5);
            getPlayScene()->EffectGroup->AddNewObject(healingLabel);

            // Set the label's visibility duration.
            labelDuration = labelDisplayTime;
        }
    }

    // Update the healing label's visibility duration.
    if (healingLabel) {
        labelDuration -= deltaTime;
        if (labelDuration <= 0) {
            getPlayScene()->EffectGroup->RemoveObject(healingLabel->GetObjectIterator());
            healingLabel = nullptr;
        }
    }
}

void FourthEnemy::OnExplode() {
    // Ensure the healing label is removed when the enemy dies.
    if (healingLabel) {
        getPlayScene()->EffectGroup->RemoveObject(healingLabel->GetObjectIterator());
        healingLabel = nullptr;
    }

    // Call the base class OnExplode method to handle the explosion effects.
    Enemy::OnExplode();
}

