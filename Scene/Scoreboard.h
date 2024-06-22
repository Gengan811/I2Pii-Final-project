//
// Created by user on 2024/5/25.
//

#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include <list>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"
extern int FinalScore;
class Scoreboard final : public Engine::IScene {
private:
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
public:
    explicit Scoreboard() = default;
    void Initialize() override;
    void Terminate() override;
    void PrevOnClick();
    void NextOnClick();
    void HomeOnClick(int stage) const;
    Group* MemberGroup;
    void Listout(int ,std::multimap <int,std::string>,std::multimap <int,std::string>);
};
#endif //SCOREBOARD_H
