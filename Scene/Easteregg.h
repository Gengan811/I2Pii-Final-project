//
// Created by user on 2024/5/28.
//

#ifndef EASTEREGG_H
#define EASTEREGG_H
#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"
class Easteregg final : public Engine::IScene {
public:
    explicit Easteregg() = default;
    void Initialize() override;
    void Terminate() override;
    void PicOnClick(int stage);
};
#endif //EASTEREGG_H
