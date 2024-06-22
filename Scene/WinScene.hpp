#ifndef WINSCENE_HPP
#define WINSCENE_HPP
#include <allegro5/allegro_audio.h>
#include "Engine/IScene.hpp"

class WinScene final : public Engine::IScene {
private:
    float ticks;
    ALLEGRO_SAMPLE_ID bgmId;
    std::string UserInput;
public:
    int FinalScore;
    Group* NameGroup;
    explicit WinScene() = default;
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void BackOnClick(int stage);
    void SaveOnClick(int stage);
    void OnKeyDown(int keycode) override;
    std::string GetCurrentDateTime();
};

#endif // WINSCENE_HPP