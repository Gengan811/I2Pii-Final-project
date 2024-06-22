#ifndef SPRITE_HPP
#define SPRITE_HPP
#include <allegro5/color.h>
#include <string>

#include "Engine/Point.hpp"
#include "Engine/IControl.hpp"
#include "UI/Component/Image.hpp"

namespace Engine {

class Sprite : public Image, public IControl {
   public:
    float Rotation;
    Point Velocity;
    // Color tint.
    ALLEGRO_COLOR Tint;
    std::list<Sprite*> lockedTurrets;
    std::list<Sprite*> lockedBullets;
    Sprite* Target = nullptr;
    // Assume a circle is a good approximation of the sprite's boundary.
    float CollisionRadius = 0;
    explicit Sprite(std::string img,
                    float x,
                    float y,
                    float w = 0,
                    float h = 0,
                    float anchorX = 0.5f,
                    float anchorY = 0.5f,
                    float rotation = 0,
                    float vx = 0,
                    float vy = 0,
                    unsigned char r = 255,
                    unsigned char g = 255,
                    unsigned char b = 255,
                    unsigned char a = 255);

    void Draw() const override;

    void Update(float deltaTime) override;
};
}  // namespace Engine
#endif  // SPRITE_HPP
