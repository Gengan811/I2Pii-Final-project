//
// Created by 胡耿安 on 2024/6/21.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <list>
#include <string>
#include <vector>

#include "Engine/IControl.hpp"
#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"

class Bullet;
class PlayScene;

class Player : public Engine::Sprite {
   protected:
    std::vector<Engine::Point> path;
    float hp;
    float atk;
    float Rotation;
    float coolDown;
    float reload = 0;
    float rotateRadian = 2 * ALLEGRO_PI;
    float speed;
    bool is_moving;
    Engine::Point TargetPosition;
    // Color tint.
    ALLEGRO_COLOR Tint;
    // Assume a circle is a good approximation of the sprite's boundary.
    float CollisionRadius = 0;
    PlayScene* getPlayScene();

   public:
    Player(std::string img,
           float x,
           float y,
           float radius,
           float speed,
           float hp);

    void Hit(float damage);
    void Update(float deltaTime) override;
    void Draw() const override;
    void OnKeyDown(int keyCode) override;
    void CreateBullet();
};
#endif  // PLAYER_HPP