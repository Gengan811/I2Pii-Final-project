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
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/LOG.hpp"
#include "Engine/Resources.hpp"
#include "Player/Seele.hpp"
#include "Player/Wolf.hpp"
#include "Scene/PlayScene.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"

int x, y, z;
int effect_x, effect_y, effect_z;
void Bonusroom::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    x = rand() % 20;
    y = rand() % 20;
    z = rand() % 20;
    if (x < 2)
        effect_x = 1;
    else if (x < 10)
        effect_x = 2;
    else if (x < 12)
        effect_x = 3;
    else if (x < 14)
        effect_x = 4;
    else if (x < 16)
        effect_x = 5;
    else if (x < 17)
        effect_x = 6;
    else if (x < 18)
        effect_x = 7;
    else if (x < 19)
        effect_x = 8;
    else if (x <= 20)
        effect_x = 9;
    if (y < 2)
        effect_y = 1;
    else if (y < 10)
        effect_y = 2;
    else if (y < 12)
        effect_y = 3;
    else if (y < 14)
        effect_y = 4;
    else if (y < 16)
        effect_y = 5;
    else if (y < 17)
        effect_y = 6;
    else if (y < 18)
        effect_y = 7;
    else if (y < 19)
        effect_y = 8;
    else if (y <= 20)
        effect_y = 9;
    if (z < 2)
        effect_z = 1;
    else if (z < 10)
        effect_z = 2;
    else if (z < 12)
        effect_z = 3;
    else if (z < 14)
        effect_z = 4;
    else if (z < 16)
        effect_z = 5;
    else if (z < 17)
        effect_z = 6;
    else if (z < 18)
        effect_z = 7;
    else if (z < 19)
        effect_z = 8;
    else if (z <= 20)
        effect_z = 9;
    std::vector<std::string> texts = {
        "ATK↑" /*10%*/,      "Heal 50%" /*40%*/, "SPD↑" /*10%*/,
        "Heal 100%" /*10%*/, "AS↑ " /*10%*/,     "AS↑↑" /*5%*/,
        "SPD↑↑" /*5%*/,      "ATK↑↑" /*5%*/,     "Shield" /*5%*/};

    Engine::ImageButton* btn;
    btn = new Engine::ImageButton(
        "bonus/bonus" + std::to_string(effect_x) + ".png",
        "bonus/bonus" + std::to_string(effect_x) + ".png", halfW,
        halfH / 2 + 200, 100, 100);
    btn->SetOnClickCallback(
        std::bind(&Bonusroom::ButtonOnClick, this, effect_x));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label(texts[effect_x - 1], "GenYoGothic-N.ttc", 60,
                                   halfW + 100, h - 250, 255, 255, 255, 250,
                                   0.5, 0.5));

    btn = new Engine::ImageButton(
        "bonus/bonus" + std::to_string(effect_y) + ".png",
        "bonus/bonus" + std::to_string(effect_y) + ".png", halfW - 200,
        halfH / 2 + 200, 100, 100);
    btn->SetOnClickCallback(
        std::bind(&Bonusroom::ButtonOnClick, this, effect_y));
    AddNewControlObject(btn);

    AddNewObject(new Engine::Label(texts[effect_y - 1], "GenYoGothic-N.ttc", 60,
                                   halfW, h - 250, 255, 255, 255, 250, 0.5,
                                   0.5));
    btn = new Engine::ImageButton(
        "bonus/bonus" + std::to_string(effect_z) + ".png",
        "bonus/bonus" + std::to_string(effect_z) + ".png", halfW - 400,
        halfH / 2 + 200, 100, 100);
    btn->SetOnClickCallback(
        std::bind(&Bonusroom::ButtonOnClick, this, effect_z));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label(texts[effect_z - 1], "GenYoGothic-N.ttc", 60,
                                   halfW + 300, h - 250, 255, 255, 255, 250,
                                   0.5, 0.5));
}

void Bonusroom::Terminate() {
    IScene::Terminate();
}
void Bonusroom::ButtonOnClick(int x) {
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
