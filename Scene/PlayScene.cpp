#include <allegro5/allegro.h>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <vector>

#include "Enemy/Enemy.hpp"
#include "Enemy/SoldierEnemy.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/LOG.hpp"
#include "Engine/Resources.hpp"
#include "PlayScene.hpp"
#include "Player/Wolf.hpp"
#include "Scene/ScoreboardScene.hpp"
#include "Turret/FourthTurret.hpp"
#include "Turret/LaserTurret.hpp"
#include "Turret/MachineGunTurret.hpp"
#include "Turret/MissileTurret.hpp"
#include "Turret/TurretButton.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "UI/Animation/Plane.hpp"
#include "UI/Component/Label.hpp"

int FinalScore;

bool PlayScene::DebugMode = true;
const std::vector<Engine::Point> PlayScene::directions = {
    Engine::Point(-1, 0), Engine::Point(0, -1), Engine::Point(1, 0),
    Engine::Point(0, 1)};
const int PlayScene::MapWidth = 25, PlayScene::MapHeight = 13;
const int PlayScene::BlockSize = 64;
const float PlayScene::DangerTime = 7.61;
const Engine::Point PlayScene::SpawnGridPoint = Engine::Point(-1, 0);
const Engine::Point PlayScene::EndGridPoint =
    Engine::Point(MapWidth, MapHeight - 1);
const std::vector<int> PlayScene::code = {
    ALLEGRO_KEY_UP,    ALLEGRO_KEY_UP,       ALLEGRO_KEY_DOWN,
    ALLEGRO_KEY_DOWN,  ALLEGRO_KEY_LEFT,     ALLEGRO_KEY_LEFT,
    ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_RIGHT,    ALLEGRO_KEY_B,
    ALLEGRO_KEY_A,     ALLEGRO_KEYMOD_SHIFT, ALLEGRO_KEY_ENTER};
Engine::Point PlayScene::GetClientSize() {
    return Engine::Point(MapWidth * BlockSize, MapHeight * BlockSize);
}
void PlayScene::Initialize() {
    // TODO: [HACKATHON-3-BUG] (1/5): There's a bug in this file, which crashes
    // the game when you lose. Try to find it.
    // TODO: [HACKATHON-3-BUG] (2/5): Find out the cheat code to test.
    // TODO: [HACKATHON-3-BUG] (2/5): It should generate a Plane, and add 10000
    // to the money, but it doesn't work now.
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    AddNewObject(new Engine::Image(
        std::string("play/background/Scene") + std::to_string(MapId) + ".png",
        0, 0, w, h));
    mapState.clear();
    keyStrokes.clear();
    ticks = 0;
    deathCountDown = -1;
    lives = 10;
    money = 150;
    // Add groups from bottom to top.
    AddNewObject(TileMapGroup = new Group());
    AddNewObject(GroundEffectGroup = new Group());
    AddNewObject(DebugIndicatorGroup = new Group());
    AddNewObject(TowerGroup = new Group());
    AddNewObject(EnemyGroup = new Group());
    AddNewObject(BulletGroup = new Group());
    AddNewObject(EffectGroup = new Group());
    // Should support buttons.
    AddNewControlObject(UIGroup = new Group());

    ConstructUI();
    CalculateBFSDistance();
    // Preload Lose Scene
    deathBGMInstance =
        Engine::Resources::GetInstance().GetSampleInstance("astronomia.ogg");
    // Start BGM.
    bgmId = AudioHelper::PlayBGM("play.ogg");
}
void PlayScene::Terminate() {
    AudioHelper::StopBGM(bgmId);
    AudioHelper::StopSample(deathBGMInstance);
    deathBGMInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}
void PlayScene::Update(float deltaTime) {
    IScene::Update(deltaTime);
    if (EnemyGroup->GetObjects().empty()) {
        // Free resources.
        if (lives <= 0)
            Engine::GameEngine::GetInstance().ChangeScene("lose-scene");
        else {
            FinalScore = lives * money / 100;
            Engine::GameEngine::GetInstance().ChangeScene("win");
        }
    }
}

void PlayScene::Draw() const {
    IScene::Draw();
    if (DebugMode) {
        // Draw reverse BFS distance on all reachable blocks.
        for (int i = 0; i < MapHeight; i++) {
            for (int j = 0; j < MapWidth; j++) {
                if (mapDistance[i][j] != -1) {
                    // Not elegant nor efficient, but it's quite enough for
                    // debugging.
                    Engine::Label label(
                        std::to_string(mapDistance[i][j]), "pirulen.ttf", 32,
                        (j + 0.5) * BlockSize, (i + 0.5) * BlockSize);
                    label.Anchor = Engine::Point(0.5, 0.5);
                    label.Draw();
                }
            }
        }
    }
}
void PlayScene::OnKeyDown(int keyCode) {
    IScene::OnKeyDown(keyCode);
}
int PlayScene::GetMoney() const {
    return money;
}
void PlayScene::EarnMoney(int money) {
    this->money += money;
    UIMoney->Text = std::string("$") + std::to_string(this->money);
}

void PlayScene::ReadMap() {
    std::string filename =
        std::string("Resource/map") + std::to_string(MapId) + ".txt";
    // Read map file.
    char c;
    std::vector<bool> mapData;
    std::ifstream fin(filename);
    while (fin >> c) {
        switch (c) {
            case '0':
                mapData.push_back(false);
                break;
            case '1':
                mapData.push_back(true);
                break;
            case '\n':
            case '\r':
                if (static_cast<int>(mapData.size()) / MapWidth != 0)
                    throw std::ios_base::failure("Map data is corrupted.");
                break;
            default:
                throw std::ios_base::failure("Map data is corrupted.");
        }
    }
    fin.close();
    // Validate map data.
    if (static_cast<int>(mapData.size()) != MapWidth * MapHeight)
        throw std::ios_base::failure("Map data is corrupted.");
    // Store map in 2d array.
    mapState = std::vector<std::vector<TileType>>(
        MapHeight, std::vector<TileType>(MapWidth));
    mapDistance = std::vector<std::vector<int>>(MapHeight,
                                                std::vector<int>(MapWidth, -1));
    for (int i = 0; i < MapHeight; i++) {
        for (int j = 0; j < MapWidth; j++) {
            const int num = mapData[i * MapWidth + j];
            mapState[i][j] = num ? TILE_EMPTY : TILE_OBSTACLE;
            if (!num)
                TileMapGroup->AddNewObject(
                    new Engine::Image("play/map_floor.png", j * BlockSize,
                                      i * BlockSize, BlockSize, BlockSize));
        }
    }
}
void PlayScene::ReadEnemy() {
    std::string filename =
        std::string("Resource/enemy") + std::to_string(MapId) + ".txt";
    // Read enemy file.
    int type, x, y;
    std::ifstream fin(filename);
    while (fin >> type && fin >> x && fin >> y) {
        switch (type) {
            case 1:
                EnemyGroup->AddNewObject(
                    new SoldierEnemy(BlockSize / 2 + BlockSize * x,
                                     BlockSize / 2 + BlockSize * y));
                break;

            default:
                break;
        }
    }
    fin.close();
}
void PlayScene::ConstructUI() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    ReadEnemy();
    ReadMap();
    // AddNewObject(new SoldierEnemy(50, 50));
    switch (CharacterId) {
        case 1:
            AddNewControlObject(player =
                                    new Wolf(BlockSize / 2 + BlockSize * 10,
                                             BlockSize / 2 + BlockSize * 10));
            break;

        default:
            break;
    }
}

void PlayScene::CalculateBFSDistance() {
    std::queue<Engine::Point> que;
    int x = static_cast<int>(floor(player->Position.x / PlayScene::BlockSize));
    int y = static_cast<int>(floor(player->Position.y / PlayScene::BlockSize));
    que.push(Engine::Point(x, y));
    mapDistance = std::vector<std::vector<int>>(MapHeight,
                                                std::vector<int>(MapWidth, -1));
    mapDistance[y][x] = 0;
    while (!que.empty()) {
        Engine::Point p = que.front();
        que.pop();
        for (auto dir : directions) {
            Engine::Point next = p + dir;
            if (next.x < 0 || next.x >= MapWidth || next.y < 0 ||
                next.y >= MapHeight)
                continue;
            if (mapDistance[next.y][next.x] != -1 ||
                mapState[next.y][next.x] != TILE_EMPTY)
                continue;
            mapDistance[next.y][next.x] = mapDistance[p.y][p.x] + 1;
            que.push(next);
        }
    }
}