#include "WinScene.hpp"
#include <stdlib.h>
#include <fstream>
#include <functional>
#include <string>
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"
#include "PlayScene.hpp"
#include "ScoreboardScene.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"

#include <ctime>

bool typein = false;
std::string name = "", date = "";

void WinScene::Initialize() {
    name = "";

    ticks = 0;
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    char Score[20];
    std::string Scoreoutput = std::to_string(FinalScore);
    line = new Engine::Label(name, "GenJyuuGothic-Regular.ttf", 48, halfW - 475,
                             halfH + 198, 255, 255, 255, 255, 0.5, 0.5);
    AddNewObject(new Engine::Image("win/WinScene.png", 0, 0, w, h));
    AddNewObject(
        new Engine::Image("play/map_floor.png", 100, 50, w - 200, h - 75));

    AddNewObject(new Engine::Label(
        "Congruatulations!", "DancingScript-VariableFont_wght.ttf", 140, halfW,
        halfH - 200, 255, 153, 19, 255, 0.5, 0.5));
    Engine::ImageButton* btn;
    AddNewObject(new Engine::Label(
        "Your Score :    ", "ChenYuluoyan-Thin-Monospaced.ttf", 120,
        halfW - 200, halfH, 255, 255, 255, 255, 0.5, 0.5));
    AddNewObject(
        new Engine::Label(Scoreoutput, "ChenYuluoyan-Thin-Monospaced.ttf", 150,
                          halfW + 150, halfH, 255, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label(
        "Enter Your Name :", "ChenYuluoyan-Thin-Monospaced.ttf", 120,
        halfW - 120, halfH + 100, 255, 255, 255, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png",
                                  "stage-select/dirt.png", halfW - 500,
                                  halfH + 150, 1000, 80);
    btn->SetOnClickCallback(std::bind(&WinScene::BarOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(TextGroup = new Engine::Group());
    btn = new Engine::ImageButton("stage-select/white.png", "win/floor.png",
                                  halfW - 200, halfH * 7 / 4 - 25, 400, 100);
    btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "GenJyuuGothic-Regular.ttf", 48,
                                   halfW, halfH * 7 / 4 + 25, 0, 0, 0, 255, 0.5,
                                   0.5));
    bgmId = AudioHelper::PlayAudio("Winmusic.ogg");
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localTime);
    date = buffer;

    // Save Score
}
void WinScene::Terminate() {
    IScene::Terminate();
    AudioHelper::StopBGM(bgmId);
}
void WinScene::Update(float deltaTime) {
    ticks += deltaTime;
    if (ticks > 4 && ticks < 100 &&
        dynamic_cast<PlayScene*>(
            Engine::GameEngine::GetInstance().GetScene("play"))
                ->MapId == 2) {
        ticks = 100;
        bgmId = AudioHelper::PlayBGM("happy.ogg");
    }
}

void WinScene::BackOnClick(int stage) {
    // Change to select scene.
    std::ofstream file;
    file.open("Resource/scoreboard.txt", std::ios::app);
    if (name == "")
        file << "Unknown " << FinalScore << " " << date << std::endl;
    else
        file << name << " " << FinalScore << " " << date << std::endl;
    file.close();
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
void WinScene::BarOnClick() {
    // Change to select scene.
    typein = true;
}
void WinScene::OnKeyDown(int keyCode) {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    IScene::OnKeyDown(keyCode);
    if (typein) {
        if (keyCode == ALLEGRO_KEY_BACKSPACE && name.size() > 0) {
            if (name.size() > 0)
                name.pop_back();
            TextGroup->Clear();

            line->Text = name;
            TextGroup->AddNewObject(
                new Engine::Label(name, "GenJyuuGothic-Regular.ttf", 48,
                                  halfW - 475 + line->GetTextWidth() * 0.5,
                                  halfH + 198, 255, 255, 255, 255, 0.5, 0.5));
        } else if (keyCode >= ALLEGRO_KEY_A && keyCode <= ALLEGRO_KEY_Z &&
                   name.size() < 10) {
            name.push_back('A' + keyCode - ALLEGRO_KEY_A);
            TextGroup->Clear();
            line->Text = name;
            TextGroup->AddNewObject(
                new Engine::Label(name, "GenJyuuGothic-Regular.ttf", 48,
                                  halfW - 475 + line->GetTextWidth() * 0.5,
                                  halfH + 198, 255, 255, 255, 255, 0.5, 0.5));
        } else if (keyCode >= ALLEGRO_KEY_0 && keyCode <= ALLEGRO_KEY_9 &&
                   name.size() < 10) {
            name.push_back('0' + keyCode - ALLEGRO_KEY_0);
            TextGroup->Clear();

            line->Text = name;
            TextGroup->AddNewObject(
                new Engine::Label(name, "GenJyuuGothic-Regular.ttf", 48,
                                  halfW - 475 + line->GetTextWidth() * 0.5,
                                  halfH + 198, 255, 255, 255, 255, 0.5, 0.5));
        } else if (keyCode == ALLEGRO_KEY_ENTER) {
            // Save Score
            typein = false;
        }
    }
}
