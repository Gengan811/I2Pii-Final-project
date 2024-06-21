#ifndef SCOREBOARDSCENE_H
#define SCOREBOARDSCENE_H
#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"

class ScoreBoardScene final : public Engine::IScene {
public:
    Group* DataGroup;
    void Initialize() override;
    void Terminate() override;
    void BackOnClick(int stage);
    void PrevPageOnClick(int stage);
    void NextPageOnClick(int stage);
    void ReadScoreBoard();
    void DisplayScores();
    void CreateButtons();

private:
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    std::vector<std::tuple<std::string, int, std::string>> scores; // Updated to store name, score, and date-time
    std::vector<Engine::Label*> scoreLabels; // Container to keep track of score labels
    int currentPage;
    const int scoresPerPage = 10;
};
#endif // SCOREBOARDSCENE_H
