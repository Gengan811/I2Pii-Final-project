#include <functional>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "StartScene.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"


void StartScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton* btn;
    AddNewObject(new Engine::Image("start/Beginning_Scene_Of_Tower.png", 0, 0, w, h));
    AddNewObject(new Engine::Label("新‧窮鐵道", "ChenYuluoyan-Thin-Monospaced.ttf", 175, halfW-250, halfH / 3 + 100, 220, 190, 30, 255, 0.5, 0.5));


    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH / 2 + 200 , 400, 100);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("開始遊戲", "GenYoGothic-N.ttc", 60, halfW, halfH / 2 + 250, 255, 255, 255, 250, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&StartScene::SettingsOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("設置", "GenYoGothic-N.ttc", 60, halfW, halfH * 3 / 2, 255, 255, 255, 250, 0.5, 0.5));

    bgmInstance = AudioHelper::PlaySample("If_I_can_stop_one_heart_from_breaking.ogg", true, AudioHelper::BGMVolume);

}
void StartScene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}
void StartScene::PlayOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
void StartScene::SettingsOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("settings");
}
