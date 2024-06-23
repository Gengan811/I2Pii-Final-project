#ifndef BULLET_HPP
#define BULLET_HPP
#include <string>

#include "Engine/Sprite.hpp"

class Enemy;
class PlayScene;
namespace Engine {
struct Point;
}  // namespace Engine

class Bullet : public Engine::Sprite {
   protected:
    float speed;
    float damage;
    Sprite* parent;
    PlayScene* getPlayScene();
    virtual void OnExplode(Enemy* enemy);

   public:
    bool fromPlayer;
    Sprite* Target = nullptr;
    explicit Bullet(std::string img,
                    float speed,
                    float damage,
                    Engine::Point position,
                    Engine::Point forwardDirection,
                    float rotation,
                    Sprite* parent, bool fromPlayer);
    void Update(float deltaTime) override;
    void Draw() const override;
    bool SlowDownEffect;
    float SlowDownFactor;
    float SlowDownDuration;
};
#endif  // BULLET_HPP
