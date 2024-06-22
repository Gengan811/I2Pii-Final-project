#include <functional>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

#include "Engine/LOG.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "WinScene.hpp"
#include "ScoreboardScene.hpp"
#include "Engine/IScene.hpp"

using Engine::LOG;

void WinScene::Initialize() {
    ticks = 0;
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    AddNewObject(new Engine::Image("win/benjamin-sad.png", halfW, halfH, 0, 0, 0.5, 0.5));
    AddNewObject(new Engine::Label("You Win!", "pirulen.ttf", 48, halfW, halfH / 4 + 30, 255, 255, 255, 255, 0.5, 0.5));
    Engine::ImageButton *btn;
    btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW + 200, halfH * 7 / 4 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&WinScene::SaveOnClick, this, 3));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Save", "pirulen.ttf", 48, halfW + 400, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("Name:", "pirulen.ttf", 48, halfW - 500, halfH / 4 - 30, 255, 255, 255, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("Score:", "pirulen.ttf", 48, halfW + 300, halfH / 4 - 30, 255, 255, 255, 255, 0.5, 0.5));

    std::string value = std::to_string(FinalScore);

    AddNewObject(new Engine::Label(value, "pirulen.ttf", 48, halfW + 500, halfH / 4 - 30, 255, 255, 255, 255, 0.5, 0.5));
    UserInput = "";
    AddNewObject(NameGroup = new Group());

    bgmId = AudioHelper::PlayAudio("win.wav");
}
void WinScene::Terminate() {
    IScene::Terminate();
    AudioHelper::StopBGM(bgmId);
}
void WinScene::Update(float deltaTime) {
    ticks += deltaTime;
    if (ticks > 4 && ticks < 100 &&
        dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
        ticks = 100;
        bgmId = AudioHelper::PlayBGM("happy.ogg");
    }
}

void WinScene::OnKeyDown(int keyCode) {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    IScene::OnKeyDown(keyCode);
    if (keyCode >= ALLEGRO_KEY_A && keyCode <= ALLEGRO_KEY_Z) {
        // Check if the length of UserInput is less than 10 before adding a new character.
        if (UserInput.length() < 10) {
            // Add the pressed key to the UserInput string.
            UserInput += (char)('A' + (keyCode - ALLEGRO_KEY_A));
            NameGroup->Clear();
            NameGroup->AddNewObject(new Engine::Label(UserInput, "pirulen.ttf", 38, halfW - 225, (halfH / 2) - 135, 255, 255, 255, 255, 0.5, 0.5));
        }
    } else if (keyCode == ALLEGRO_KEY_BACKSPACE && !UserInput.empty()) {
        // Remove the last character on backspace.
        UserInput.pop_back();
        NameGroup->Clear();
        NameGroup->AddNewObject(new Engine::Label(UserInput, "pirulen.ttf", 38, halfW - 225, (halfH / 2) - 135, 255, 255, 255, 255, 0.5, 0.5));
    }
}
void WinScene::BackOnClick(int stage) {
    // Change to select scene.
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
void WinScene::SaveOnClick(int stage) {
    // LOG() << "save on click";
    // Save the score to the file.
    std::ofstream ofs("Resource/scoreboard.txt", std::ofstream::app);
    ofs << UserInput << ' ' << FinalScore << ' ' << GetCurrentDateTime() << std::endl;
    ofs.close();
    // Change to select scene.
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}

std::string WinScene::GetCurrentDateTime() {
    std::time_t now = std::time(nullptr);
    char buf[100];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return buf;
}
