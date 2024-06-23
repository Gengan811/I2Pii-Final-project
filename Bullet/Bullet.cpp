#include "Bullet.hpp"
#include "Engine/Collider.hpp"
#include "Enemy/Enemy.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IObject.hpp"
#include "Engine/IScene.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"
#include "Player/Player.hpp"
#include "Scene/PlayScene.hpp"

PlayScene* Bullet::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

void Bullet::OnExplode(Enemy* enemy) {}

Bullet::Bullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Sprite* parent) :
	Sprite(img, position.x, position.y), speed(speed), damage(damage), parent(parent) {
	Velocity = forwardDirection.Normalize() * speed;
	Rotation = rotation;
	CollisionRadius = 4;
    SlowDownEffect = false;
    SlowDownFactor = 1.0f;
    SlowDownDuration = 0;
}

void Bullet::Update(float deltaTime) {
	Sprite::Update(deltaTime);
	PlayScene* scene = getPlayScene();
	// Can be improved by Spatial Hash, Quad Tree, ...
	// However, simply loop through all enemies is enough for this program.
	for (auto& it : scene->EnemyGroup->GetObjects()) {
		Enemy* enemy = dynamic_cast<Enemy*>(it);
		if (!enemy->Visible)
			continue;
		if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, enemy->Position, enemy->CollisionRadius)) {
			OnExplode(enemy);
			enemy->Hit(damage);
            // if (SlowDownEffect)
            //     enemy->ApplySlowDown(SlowDownFactor, SlowDownDuration);
			getPlayScene()->BulletGroup->RemoveObject(objectIterator);
			return;
		}
	}
	// Check if out of boundary.
    int x = Position.x / PlayScene::BlockSize;
    int y = Position.y / PlayScene::BlockSize;
	if (!Engine::Collider::IsRectOverlap(Position - Size / 2, Position + Size / 2,
                                         Engine::Point(0, 0), PlayScene::GetClientSize())
        || getPlayScene()->mapState[y][x] != PlayScene::TILE_EMPTY)
		getPlayScene()->BulletGroup->RemoveObject(objectIterator);
}
