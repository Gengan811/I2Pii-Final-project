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
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "PlayScene.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/Slider.hpp"

void CharacterSelectScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton* btn;

    PlayScene* scene = dynamic_cast<PlayScene*>(
        Engine::GameEngine::GetInstance().GetScene("play"));
    scene->StageID = 1;

    AddNewObject(new Engine::Label("!! Choose Your Hero !!", "pirulen.ttf", 80,
                                   halfW, halfH / 3, 10, 255, 255, 255, 0.5,
                                   0.5));

    btn = new Engine::ImageButton("character/wolf.png", "character/wolf.png",
                                  halfW - 450, halfH / 2, 350, 350);
    btn->SetOnClickCallback(
        std::bind(&CharacterSelectScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Sliver wolf", "pirulen.ttf", 32,
                                   halfW - 325, halfH / 2 + 500, 255, 255, 255,
                                   255, 0.5, 0.5));

    btn = new Engine::ImageButton("character/seele.png", "character/seele.png",
                                  halfW + 100, halfH / 2, 350, 350);
    btn->SetOnClickCallback(
        std::bind(&CharacterSelectScene::PlayOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Seele", "pirulen.ttf", 32, halfW + 275,
                                   halfH / 2 + 500, 255, 255, 255, 255, 0.5,
                                   0.5));

    // Not safe if release resource while playing, however we only free while
    // change scene, so it's fine.
    bgmInstance =
        AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);
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
    PlayScene* scene = dynamic_cast<PlayScene*>(
        Engine::GameEngine::GetInstance().GetScene("play"));
    scene->CharacterId = character_id;
    Engine::GameEngine::GetInstance().ChangeScene("play");
}