#ifndef WINSCENE_HPP
#define WINSCENE_HPP
#include <allegro5/allegro_audio.h>
#include "Engine/IScene.hpp"
#include "UI/Component/Label.hpp"

class WinScene final : public Engine::IScene {
   private:
    float ticks;
    ALLEGRO_SAMPLE_ID bgmId;

   public:
    explicit WinScene() = default;
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void BackOnClick(int stage);
    void BarOnClick();
    Group* TextGroup;
    void OnKeyDown(int keyCode) override;
    Engine::Label* line;
};

#endif  // WINSCENE_HPP