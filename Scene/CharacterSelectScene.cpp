//
// Created by 胡耿安 on 2024/6/21.
//

#include "CharacterSelectScene.hpp"
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

void CharacterSelectScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton* btn;

    AddNewObject(new Engine::Label("!! Choose Your Hero !!", "pirulen.ttf", 120, halfW, halfH / 3 + 50, 10, 255, 255, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("character/sliver-wolf.png", "stage-select/sliver-wolf.png", halfW - 250, halfH / 2, 400, 100);
    btn->SetOnClickCallback(std::bind(&CharacterSelectScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("銀狼", "pirulen.ttf", 48, halfW - 50, halfH / 2 + 200, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/super-brother.png", "stage-select/super-brother.png", halfW - 150, halfH /2, 400, 100);
    btn->SetOnClickCallback(std::bind(&CharacterSelectScene::PlayOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("超哥", "pirulen.ttf", 48, halfW + 50, halfH / 2 + 100, 0, 0, 0, 255, 0.5, 0.5));

    // Not safe if release resource while playing, however we only free while change scene, so it's fine.
    bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);
}
void CharacterSelectScene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}
void CharacterSelectScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("start");
}
void CharacterSelectScene::PlayOnClick(int character_id) {
    PlayScene* scene = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
    scene->character = character_id;
    Engine::GameEngine::GetInstance().ChangeScene("play");
}