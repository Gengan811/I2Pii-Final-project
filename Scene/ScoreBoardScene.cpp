#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "UI/Component/Slider.hpp"
#include "ScoreBoardScene.hpp"
#include "Engine/Group.hpp"

void ScoreBoardScene::Initialize() {
    AddNewObject(DataGroup = new Group());
    ReadScoreBoard();
    currentPage = 0;
    CreateButtons();
    DisplayScores();

    // Not safe if release resource while playing, however we only free while change scene, so it's fine.
    bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);
}

void ScoreBoardScene::CreateButtons() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    Engine::ImageButton* btn;
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 700, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::PrevPageOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Prev Page", "pirulen.ttf", 48, halfW - 500, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 300, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::NextPageOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Next Page", "pirulen.ttf", 48, halfW + 500, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));
}

void ScoreBoardScene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}

void ScoreBoardScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}

void ScoreBoardScene::PrevPageOnClick(int stage) {
    if (currentPage > 0) {
        DataGroup->Clear();
        currentPage--;
        DisplayScores();
    }
}

void ScoreBoardScene::NextPageOnClick(int stage) {
    if ((currentPage + 1) * scoresPerPage < scores.size()) {
        DataGroup->Clear();
        currentPage++;
        DisplayScores();
    }
}

void ScoreBoardScene::DisplayScores() {
    int halfW = Engine::GameEngine::GetInstance().GetScreenSize().x / 2;
    int halfH = Engine::GameEngine::GetInstance().GetScreenSize().y / 2;

    // Display scores for the current page
    int start = currentPage * scoresPerPage;
    int end = std::min(start + scoresPerPage, static_cast<int>(scores.size()));

    AddNewObject(new Engine::Label("Scoreboard", "pirulen.ttf", 48, halfW, halfH / 2 - 150, 0, 255, 0, 255, 0.5, 0.5));

    for (int i = start; i < end; ++i) {
        const auto& [name, score, datetime] = scores[i];
        std::string text = name + " " + std::to_string(score) + " " + datetime;
        DataGroup->AddNewObject(new Engine::Label(text, "pirulen.ttf", 38, halfW + 500, (halfH / 2) - 100 + (i - start) * 50, 0, 180, 0, 255, 1, 0.5));
    }
}

void ScoreBoardScene::ReadScoreBoard() {
    std::string filename = "Resource/scoreboard.txt";
    std::ifstream fin(filename);

    if (!fin) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string name, datetime;
    int score;
    scores.clear();  // Clear any existing data

    while (fin >> name >> score >> std::ws && std::getline(fin, datetime)) {
        scores.emplace_back(name, score, datetime);
    }

    std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) {
        return std::get<1>(a) > std::get<1>(b);
    });

    // Debug
    std::cout << "Scores loaded from file:" << std::endl;
    for (const auto& entry : scores) {
        std::cout << std::get<0>(entry) << " " << std::get<1>(entry) << " " << std::get<2>(entry) << std::endl;
    }
}
