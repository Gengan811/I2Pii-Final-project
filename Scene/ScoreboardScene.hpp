//
// Created by user on 2024/5/25.
//

#ifndef SCOREBOARDSCENE_HPP
#define SCOREBOARDSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <fstream>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "Engine/IScene.hpp"

class ScoreboardScene final : public Engine::IScene {
   private:
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;

   public:
    int FinalScore;
    explicit ScoreboardScene() = default;
    void Initialize() override;
    void Terminate() override;
    void PrevOnClick();
    void NextOnClick();
    void HomeOnClick(int stage) const;
    Group* MemberGroup;
    void Listout(int,
                 std::multimap<int, std::string>,
                 std::multimap<int, std::string>);
};
#endif  // SCOREBOARDSCENE_HPP
