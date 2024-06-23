#include "Bonusroom.hpp"
#include <allegro5/allegro.h>
#include <algorithm>
#include <cmath>
#include <cstdlib>
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
#include "Player/Seele.hpp"
#include "Player/Wolf.hpp"
#include "Scene/PlayScene.hpp"
#include "UI/Component/Label.hpp"

int x, y, z;
int effect_x, effect_y, effect_z;
void Bonusroom::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    x = rand() % 21;
    y = rand() % 21;
    z = rand() % 21;
    switch (x) {
        case x < 2:
            effect_x = 1;
            break;
        case x < 10:
            effect_x = 2;
            break;
        case x < 12:
            effect_x = 3;
            break;
        case x < 14:
            effect_x = 4;
            break;
        case x < 16:
            effect_x = 5;
            break;
        case x < 17:
            effect_x = 6;
            break;
        case x < 18:
            effect_x = 7;
            break;
        case x < 19:
            effect_x = 8;
            break;
        case x < 20:
            effect_x = 9;
            break;
        default:
            break;
    }
    switch (y) {
        case y < 2:
            effect_y = 1;
            break;
        case y < 10:
            effect_y = 2;
            break;
        case y < 12:
            effect_y = 3;
            break;
        case y < 14:
            effect_y = 4;
            break;
        case y < 16:
            effect_y = 5;
            break;
        case y < 17:
            effect_y = 6;
            break;
        case y < 18:
            effect_y = 7;
            break;
        case y < 19:
            effect_y = 8;
            break;
        case y < 20:
            effect_y = 9;
            break;
        default:
            break;
    }
    switch (z) {
        case z < 2:
            effect_z = 1;
            break;
        case z < 10:
            effect_z = 2;
            break;
        case z < 12:
            effect_z = 3;
            break;
        case z < 14:
            effect_z = 4;
            break;
        case z < 16:
            effect_z = 5;
            break;
        case z < 17:
            effect_z = 6;
            break;
        case z < 18:
            effect_z = 7;
            break;
        case z < 19:
            effect_z = 8;
            break;
        case z < 20:
            effect_z = 9;
            break;
        default:
            break;
    }

    std::vector<std::string> texts = {
        "ATK↑" /*10%*/,      "Heal 50%" /*40%*/, "SPD↑" /*10%*/,
        "Heal 100%" /*10%*/, "AS↑ " /*10%*/,     "AS↑↑" /*5%*/,
        "SPD↑↑" /*5%*/,      "ATK↑↑" /*5%*/,     "Shield" /*5%*/};

    Engine::ImageButton* btn;
    btn = new Engine::ImageButton(
        "bonus/bonus" + std::to_string(effect_x) + ".png",
        "bonus/bonus" + std::to_string(effect_x) + ".png", halfW - 200,
        halfH / 2 + 200, 200, 400);
    btn->SetOnClickCallback(
        std::bind(&Bonusroom::ButtonOnClick, this, effect_x));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label(texts[effect_x], "GenYoGothic-N.ttc", 60,
                                   halfW - 300, h - 250, 255, 255, 255, 250,
                                   0.5, 0.5));

    btn = new Engine::ImageButton(
        "bonus/bonus" + std::to_string(effect_y) + ".png",
        "bonus/bonus" + std::to_string(effect_y) + ".png", halfW - 200,
        halfH / 2 + 200, 200, 400);
    btn->SetOnClickCallback(
        std::bind(&Bonusroom::ButtonOnClick, this, effect_y));
    AddNewControlObject(btn);

    AddNewObject(new Engine::Label(texts[effect_y], "GenYoGothic-N.ttc", 60,
                                   halfW, h - 250, 255, 255, 255, 250, 0.5,
                                   0.5));
    btn = new Engine::ImageButton("stage-select/dirt.png",
                                  "stage-select/floor.png", halfW - 200,
                                  halfH / 2 + 200, 200, 400);
    btn->SetOnClickCallback(
        std::bind(&Bonusroom::ButtonOnClick, this, effect_z));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label(texts[effect_z], "GenYoGothic-N.ttc", 60,
                                   halfW + 300, h - 250, 255, 255, 255, 250,
                                   0.5, 0.5));
}

void Bonusroom::Terminate() {
    IScene::Terminate();
}
void Bonusroom::ButtonOnClick(int x) {
    ;
    PlayScene* play_scene = dynamic_cast<PlayScene*>(
        Engine::GameEngine::GetInstance().GetScene("play"));
    Player* player = play_scene->player;
    play_scene->StageID++;
    switch (x) {
        case 1:
            player->atk *= 1.2;
            break;
        case 2:
            if (player->hp > 15)
                player->hp = 30;
            else
                player->hp += 15;
            break;
        case 3:
            player->speed *= 1.2;
            break;
        case 4:
            player->hp = 30;
            break;
        case 5:
            player->coolDown *= 0.8;
            break;
        case 6:
            player->coolDown *= 0.6;
            break;
        case 7:
            player->speed *= 1.5;
            break;
        case 8:
            player->atk *= 1.5;
            break;
        case 9:
            player->shield += 3;
            break;
        default:
            break;
    }
    Engine::GameEngine::GetInstance().ChangeScene("play");
}