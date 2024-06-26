#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <list>
#include <memory>
#include <utility>
#include <vector>

#include "Engine/IScene.hpp"
#include "Engine/Point.hpp"
#include "Player/Player.hpp"

class RangedPlayer;
namespace Engine {
class Group;
class Image;
class Label;
class Sprite;
}  // namespace Engine

class PlayScene final : public Engine::IScene {
   private:
    ALLEGRO_SAMPLE_ID bgmId;
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> deathBGMInstance;

   protected:
    int lives;
    int money;

   public:
    enum TileType {
        TILE_OBSTACLE,
        TILE_EMPTY,
        TILE_SLOW,
    };
    static bool DebugMode;
    static const std::vector<Engine::Point> directions;
    static const int MapWidth, MapHeight;
    static const int BlockSize;
    static const float DangerTime;
    static const Engine::Point SpawnGridPoint;
    static const Engine::Point EndGridPoint;
    static const std::vector<int> code;
    int MapId;
    int StageID;
    int CharacterId;
    float ticks;
    float deathCountDown;
    // Map tiles.
    Group* TileMapGroup;
    Group* GroundEffectGroup;
    Group* DebugIndicatorGroup;
    Group* BulletGroup;
    Group* TowerGroup;
    Group* EnemyGroup;
    Group* EffectGroup;
    Group* UIGroup;
    Player* player;
    Engine::Label* UIMoney;
    Engine::Label* UILives;
    Engine::Image* imgTarget;
    Engine::Sprite* dangerIndicator;
    std::vector<std::vector<TileType>> mapState;
    std::vector<std::vector<int>> mapDistance;
    std::list<std::pair<int, float>> enemyWaveData;
    std::list<int> keyStrokes;
    static Engine::Point GetClientSize();
    explicit PlayScene() = default;
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void Draw() const override;
    void OnKeyDown(int keyCode) override;
    void ReadMap();
    void ReadEnemy();
    void ReadPlayer();
    void ConstructUI();
    void UIBtnClicked(int id);
    void CalculateBFSDistance();
    bool CheckSpaceValid(int x, int y);
    bool CheckPixelValid(int x, int y);
};
#endif  // PLAYSCENE_HPP
