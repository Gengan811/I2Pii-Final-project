//
// Created by user on 2024/5/28.
//
#include <functional>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "StartScene.h"
#include "Easteregg.h"
#include "Engine/Point.hpp"

void Easteregg::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton* btn;
    btn = new Engine::ImageButton("start/easteregg.png", "start/easteregg.png", 0, 0, w, h);
    btn->SetOnClickCallback(std::bind(&Easteregg::PicOnClick, this, 1));
    AddNewControlObject(btn);
}
void Easteregg::Terminate() {
    IScene::Terminate();
}
void Easteregg::PicOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("start");
}