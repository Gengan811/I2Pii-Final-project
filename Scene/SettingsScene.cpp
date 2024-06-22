#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "UI/Component/Slider.hpp"
#include "SettingsScene.hpp"

#include "LoseScene.hpp"


void SettingsScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;


    Engine::ImageButton *btn;
    AddNewObject(new Engine::Image("setting/Beginning_Scene_Of_Tower_cover.png", 0, 0, w, h));
    AddNewObject(new Engine::Image("setting/black.png", 300, 125, halfW+190, halfH+140));
    btn = new Engine::ImageButton("setting/exit_up.png", "setting/exit_down.png", halfW + 400, halfH - 270, 75, 75);
    btn->SetOnClickCallback(std::bind(&SettingsScene::BackOnClick, this, 2));
    AddNewControlObject(btn);

    Slider *sliderBGM, *sliderSFX;
    sliderBGM = new Slider(40 + halfW - 195, halfH - 100 - 2, 450, 4);
    sliderBGM->SetOnValueChangedCallback(
            std::bind(&SettingsScene::BGMSlideOnValueChanged, this, std::placeholders::_1));
    AddNewControlObject(sliderBGM);
    AddNewObject(
            new Engine::Label("BGM: ", "pirulen.ttf", 28, 40 + halfW - 60 - 195, halfH - 100, 255, 255, 255, 255, 0.5,
                              0.5));
    sliderSFX = new Slider(40 + halfW - 195, halfH + 100 - 2, 450, 4);
    sliderSFX->SetOnValueChangedCallback(
            std::bind(&SettingsScene::SFXSlideOnValueChanged, this, std::placeholders::_1));
    AddNewControlObject(sliderSFX);
    AddNewObject(
            new Engine::Label("SFX: ", "pirulen.ttf", 28, 40 + halfW - 60 - 195, halfH +100, 255, 255, 255, 255, 0.5,
                              0.5));
    // Not safe if release resource while playing, however we only free while change scene, so it's fine.
    bgmInstance = AudioHelper::PlaySample("paimon.ogg", true, AudioHelper::BGMVolume);
    sliderBGM->SetValue(AudioHelper::BGMVolume);
    sliderSFX->SetValue(AudioHelper::SFXVolume);
}
void SettingsScene::BackOnClick(int stage) {
    // Change to select scene.
    Engine::GameEngine::GetInstance().ChangeScene("start");
}
void SettingsScene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}

void SettingsScene::PlayOnClick(int stage) {
    PlayScene *scene = dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetScene("play"));
    scene->MapId = stage;
    Engine::GameEngine::GetInstance().ChangeScene("play");
}

void SettingsScene::BGMSlideOnValueChanged(float value) {
 //派蒙
    AudioHelper::ChangeSampleVolume(bgmInstance, value);
    AudioHelper::BGMVolume = value;
}

void SettingsScene::SFXSlideOnValueChanged(float value) {
    AudioHelper::SFXVolume = value;
}
