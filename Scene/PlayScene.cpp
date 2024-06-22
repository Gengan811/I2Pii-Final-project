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
#include "Enemy/FourthEnemy.hpp"
#include "Enemy/PlaneEnemy.hpp"
#include "Enemy/SoldierEnemy.hpp"
#include "Enemy/TankEnemy.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/LOG.hpp"
#include "Engine/Resources.hpp"
#include "PlayScene.hpp"
#include "Player/Wolf.hpp"
#include "Scene/ScoreboardScene.hpp"
#include "Scene/WinScene.hpp"
#include "Turret/FourthTurret.hpp"
#include "Turret/LaserTurret.hpp"
#include "Turret/MachineGunTurret.hpp"
#include "Turret/MissileTurret.hpp"
#include "Turret/TurretButton.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "UI/Animation/Plane.hpp"
#include "UI/Component/Label.hpp"

bool PlayScene::DebugMode = true;
const std::vector<Engine::Point> PlayScene::directions = {
    Engine::Point(-1, 0), Engine::Point(0, -1), Engine::Point(1, 0),
    Engine::Point(0, 1)};
const int PlayScene::MapWidth = 20, PlayScene::MapHeight = 13;
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
    mapDistance = CalculateBFSDistance();
    // Preload Lose Scene
    deathBGMInstance =
        Engine::Resources::GetInstance().GetSampleInstance("astronomia.ogg");
    Engine::Resources::GetInstance().GetBitmap("lose/benjamin-happy.png");
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
    if (EnemyGroup->GetObjects().empty()) {
        // Free resources.
        if (lives <= 0)
            Engine::GameEngine::GetInstance().ChangeScene("lose-scene");
        else {
            WinScene* scene = dynamic_cast<WinScene*>(
                Engine::GameEngine::GetInstance().GetScene("win"));
            scene->FinalScore = lives * money / 100;
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

void PlayScene::SetupLevel() {
    ReadMap();
    ReadEnemy();
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
    for (int i = 0; i < MapHeight; i++) {
        for (int j = 0; j < MapWidth; j++) {
            const int num = mapData[i * MapWidth + j];
            mapState[i][j] = num ? TILE_EMPTY : TILE_OBSTACLE;
            if (num)
                TileMapGroup->AddNewObject(
                    new Engine::Image("play/floor.png", j * BlockSize,
                                      i * BlockSize, BlockSize, BlockSize));
            else
                TileMapGroup->AddNewObject(
                    new Engine::Image("play/dirt.png", j * BlockSize,
                                      i * BlockSize, BlockSize, BlockSize));
        }
    }
}
void PlayScene::ReadEnemy() {
    // TODO: [HACKATHON-3-BUG] (3/5): Trace the code to know how the enemies are
    // created.
    // TODO: [HACKATHON-3-BUG] (3/5): There is a bug in these files, which let
    // the game only spawn the first enemy, try to fix it.
    std::string filename =
        std::string("Resource/enemy") + std::to_string(MapId) + ".txt";
    // Read enemy file.
    int type, x, y;
    std::ifstream fin(filename);
    while (fin >> type && fin >> x && fin >> y) {
        switch (type) {
            case 1:
                EnemyGroup->AddNewObject(new SoldierEnemy(x, y));
                break;

            default:
                break;
        }
    }
    fin.close();
}
void PlayScene::ConstructUI() {
    ReadMap();
    ReadEnemy();

    switch (CharacterId) {
        case 1:
            AddNewControlObject(player = new Wolf(0, 50));
            break;

        default:
            break;
    }
}

bool PlayScene::CheckSpaceValid(int x, int y) {
    if (x < 0 || x >= MapWidth || y < 0 || y >= MapHeight)
        return false;
    auto map00 = mapState[y][x];
    mapState[y][x] = TILE_OBSTACLE;
    std::vector<std::vector<int>> map = CalculateBFSDistance();
    mapState[y][x] = map00;
    if (map[0][0] == -1)
        return false;
    for (auto& it : EnemyGroup->GetObjects()) {
        Engine::Point pnt;
        pnt.x = floor(it->Position.x / BlockSize);
        pnt.y = floor(it->Position.y / BlockSize);
        if (pnt.x < 0)
            pnt.x = 0;
        if (pnt.x >= MapWidth)
            pnt.x = MapWidth - 1;
        if (pnt.y < 0)
            pnt.y = 0;
        if (pnt.y >= MapHeight)
            pnt.y = MapHeight - 1;
        if (map[pnt.y][pnt.x] == -1)
            return false;
    }
    // All enemy have path to exit.
    mapState[y][x] = TILE_OBSTACLE;
    mapDistance = map;
    for (auto& it : EnemyGroup->GetObjects())
        dynamic_cast<Enemy*>(it)->UpdatePath(mapDistance);
    return true;
}
std::vector<std::vector<int>> PlayScene::CalculateBFSDistance() {
    // Reverse BFS to find path.
    std::vector<std::vector<int>> map(
        MapHeight, std::vector<int>(std::vector<int>(MapWidth, -1)));
    std::queue<Engine::Point> que;
    // Push end point.
    // BFS from end point.
    if (mapState[MapHeight - 1][MapWidth - 1] != TILE_OBSTACLE)
        return map;
    que.push(Engine::Point(MapWidth - 1, MapHeight - 1));
    map[MapHeight - 1][MapWidth - 1] = 0;
    while (!que.empty()) {
        Engine::Point p = que.front();
        que.pop();
        // TODO: [BFS PathFinding] (1/1): Implement a BFS starting from the most
        // right-bottom block in the map.
        //               For each step you should assign the corresponding
        //               distance to the most right-bottom block. mapState[y][x]
        //               is TILE_OBSTACLE if it is empty.
        for (auto dir : directions) {
            Engine::Point next = p + dir;
            if (next.x < 0 || next.x >= MapWidth || next.y < 0 ||
                next.y >= MapHeight)
                continue;
            if (map[next.y][next.x] != -1 ||
                mapState[next.y][next.x] != TILE_OBSTACLE)
                continue;
            map[next.y][next.x] = map[p.y][p.x] + 1;
            que.push(next);
        }
    }
    return map;
}