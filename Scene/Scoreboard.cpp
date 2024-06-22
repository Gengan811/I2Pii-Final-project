#include <functional>
#include <string>
#include<map>
#include <memory>
#include<algorithm>
#include<vector>
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Scoreboard.h"
#include <fstream>
#include <iostream>
int page = 1,members=0,w,h,halfW,halfH;
std::multimap <int,std::string> scoremap;
std::multimap<int,std::string> datetime;
void Scoreboard::Listout(int page,std::multimap <int,std::string> scoremap, std::multimap<int,std::string> datetime){

    AddNewObject(MemberGroup = new Engine::Group());
    MemberGroup->AddNewObject(new Engine::Label("Name", "WenQuanYi Bitmap Song 14px.ttf", 60, 200, halfH / 4 + 100, 255, 255, 255, 250, 0.5, 0.5));
    MemberGroup->AddNewObject(new Engine::Label("Score", "WenQuanYi Bitmap Song 14px.ttf", 60, halfW-100, halfH / 4 + 100, 255, 255, 255, 250, 0.5, 0.5));
    MemberGroup->AddNewObject(new Engine::Label("Date time", "WenQuanYi Bitmap Song 14px.ttf", 60, halfW+400, halfH / 4 + 100, 255, 255, 255, 250, 0.5, 0.5));
    MemberGroup->AddNewObject(new Engine::Label("------------------------------------------------", "WenQuanYi Bitmap Song 14px.ttf", 60, halfW, halfH / 4 + 150, 255, 255, 255, 250, 0.5, 0.5));
    MemberGroup->AddNewObject(new Engine::Label("Page "+std::to_string(page), "WenQuanYi Bitmap Song 14px.ttf", 48, halfW, halfH * 3 / 2 +165, 255, 255, 255, 250, 0.5, 0.5));
    int i=0;
    auto it2 = datetime.rbegin();
    for (auto it = scoremap.rbegin(); it != scoremap.rend(); it++) {
        if(i>=5*(page-1)&&i<5*page){
            MemberGroup->AddNewObject(new Engine::Label(it->second, "WenQuanYi Bitmap Song 14px.ttf", 48, 200, halfH / 4 + 225+ 65 * (i%5), 255, 255, 255, 250, 0.5, 0.5));
            MemberGroup->AddNewObject(new Engine::Label(std::to_string(it->first), "WenQuanYi Bitmap Song 14px.ttf", 60, halfW-100, halfH / 4 + 225 + 65 * (i%5), 255, 255, 0, 255, 0.5, 0.5));
            MemberGroup->AddNewObject(new Engine::Label(it2->second, "WenQuanYi Bitmap Song 14px.ttf", 48, halfW+450, halfH / 4 + 225 + 65 * (i%5), 127, 252, 10, 255, 0.5, 0.5));
        }
        i++;
        it2++;
    }

}

void Scoreboard::Initialize() {
    page =1;
    members = 0;
    w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    halfW = w / 2;
    halfH = h / 2;
    Engine::ImageButton* btn;
    AddNewObject(new Engine::Image("setting/Scoreboard.png", 0, 0, w, h));
    AddNewObject(new Engine::Label("Scoreboard", "GenJyuuGothic-Regular.ttf", 90, halfW, halfH / 8 + 50, 254, 67, 100, 255, 0.5, 0.5));
    AddNewObject(new Engine::Image("stage-select/dirt.png", 50, halfH / 8 + 100, halfW+700, halfH+100));
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 700, halfH * 3 / 2 +100 , 400, 100);
    btn->SetOnClickCallback(std::bind(&Scoreboard::PrevOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Prev", "Mamelon-4-Hi-Regular.otf", 60, halfW -500, halfH * 3 / 2 +160, 255, 255, 255, 250, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW+300, halfH * 3 / 2 + 100, 400, 100);
    btn->SetOnClickCallback(std::bind(&Scoreboard::NextOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Next", "Mamelon-4-Hi-Regular.otf", 60, halfW+500, halfH * 3 / 2 +160, 255, 255, 255, 250, 0.5, 0.5));
    btn = new Engine::ImageButton("stage-select/home.png", "stage-select/home-1.png", w - 150, 50, 100, 100);
    btn->SetOnClickCallback(std::bind(&Scoreboard::HomeOnClick, this,1));
    AddNewControlObject(btn);
    scoremap.clear();
    datetime.clear();
    std::string filename = std::string("Resource/scoreboard") + ".txt";
    // Read enemy file.
    std::string name,date,time;
    int score;
    std::ifstream fin(filename);
    while (fin >> name && fin >> score) {
        scoremap.insert(std::pair<int,std::string>(score,name));
        members++;
            fin>>date>>time;
            date = date + " " + time;
            datetime.insert(std::pair<int,std::string>(score,date));
    }
    fin.close();
    Listout(page,scoremap,datetime);
    bgmInstance = AudioHelper::PlaySample("scoreboard_music.ogg", true, AudioHelper::BGMVolume);

}
void Scoreboard::HomeOnClick(int stage) const {
    MemberGroup->Clear();
    Engine::GameEngine::GetInstance().ChangeScene("start");
}
void Scoreboard::PrevOnClick() {
    MemberGroup->Clear();
    if(page>1)
        page--;
    Listout(page,scoremap,datetime);
}
void Scoreboard::NextOnClick() {
    MemberGroup->Clear();
    if(members-page*5>0)
        page++;
    Listout(page,scoremap,datetime);
}

void Scoreboard::Terminate() {
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}
