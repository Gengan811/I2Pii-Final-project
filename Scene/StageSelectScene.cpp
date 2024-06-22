#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "UI/Component/Slider.hpp"
#include "StageSelectScene.hpp"

void StageSelectScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    AddNewObject(new Engine::Image("stage-select/background.png", 0, 0, w, h));
    Engine::ImageButton* btn;

    btn = new Engine::ImageButton("stage-select/home.png", "stage-select/home-1.png", w - 150, 50, 100, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::HomeOnClick, this, 1));
    AddNewControlObject(btn);

    btn = new Engine::ImageButton("stage-select/button.png", "stage-select/button_click.png", 160 , halfH-150 , 225,225);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);

    btn = new Engine::ImageButton("stage-select/button.png", "stage-select/button_click.png", halfW-55 , halfH / 5- 50, 225,225);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 2));
    AddNewControlObject(btn);

    btn = new Engine::ImageButton("stage-select/button.png", "stage-select/button_click.png", w-400 , halfH+115 , 225,225);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 3));
    AddNewControlObject(btn);

    btn = new Engine::ImageButton("stage-select/white.png", "stage-select/floor.png", 150, h-150, 300, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::ScoreboardOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("→ Scoreboard", "GenJyuuGothic-Regular.ttf", 36, 300, h-100, 0, 0, 0, 255, 0.5, 0.5));

    bgmInstance = AudioHelper::PlaySample("take the journey.ogg", true, AudioHelper::BGMVolume);
}
void StageSelectScene::Terminate() {
AudioHelper::StopSample(bgmInstance);
bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
IScene::Terminate();
}
void StageSelectScene::HomeOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("start");
}
void StageSelectScene::PlayOnClick(int stage) {
    PlayScene* scene = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
    scene->MapId = stage;
    Engine::GameEngine::GetInstance().ChangeScene("character-select");
}
void StageSelectScene::ScoreboardOnClick() {
    Engine::GameEngine::GetInstance().ChangeScene("scoreboard");
}