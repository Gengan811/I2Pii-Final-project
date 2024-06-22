//
// Created by 胡耿安 on 2024/6/21.
//

#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_PLAYER_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_PLAYER_HPP
#include <list>
#include <string>
#include <vector>

#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"

class Bullet;
class PlayScene;
class Turret;

class Player : public Engine::Image {
   protected:
    std::vector<Engine::Point> path;
    float hp;
    int x, y;
    float Rotation;
    // Color tint.
    ALLEGRO_COLOR Tint;
    // Assume a circle is a good approximation of the sprite's boundary.
    float CollisionRadius = 0;
    PlayScene* getPlayScene();

   public:
    std::list<Turret*> lockedTurrets;
    std::list<Bullet*> lockedBullets;
    explicit Player(std::string img,
                    float x,
                    float y,
                    float w = 0,
                    float h = 0,
                    float anchorX = 0.5f,
                    float anchorY = 0.5f,
                    float rotation = 0);

    void Hit(float damage);
    void Update(float deltaTime) override;
    void Draw() const override;
    void OnKeyDown(int keyCode);
};
#endif  // INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_PLAYER_HPP