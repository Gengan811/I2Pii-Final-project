//
// Created by 胡耿安 on 2024/6/21.
//

#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_CHARACTERSELECTSCENE_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_CHARACTERSELECTSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"

class CharacterSelectScene final : public Engine::IScene {
private:
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
public:
    explicit CharacterSelectScene() = default;
    void Initialize() override;
    void Terminate() override;
    void PlayOnClick(int CharacterId);
    void BackOnClick(int CharacterId);
};

#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_CHARACTERSELECTSCENE_HPP
