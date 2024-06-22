// [main.cpp]
// This is the entry point of your game.
// You can register your scenes here, and start the game.
#include "Engine/GameEngine.hpp"
#include "Engine/LOG.hpp"
#include "Scene/CharacterSelectScene.hpp"
#include "Scene/LoseScene.hpp"
#include "Scene/PlayScene.hpp"
#include "Scene/ScoreBoardScene.hpp"
#include "Scene/StageSelectScene.hpp"
#include "Scene/StartScene.h"
#include "Scene/WinScene.hpp"

int main(int argc, char** argv) {
    Engine::LOG::SetConfig(true);
    Engine::GameEngine& game = Engine::GameEngine::GetInstance();

    game.AddNewScene("play", new PlayScene());
    game.AddNewScene("lose-scene", new LoseScene());
    game.AddNewScene("win", new WinScene());
    game.AddNewScene("stage-select", new StageSelectScene());
    game.AddNewScene("character-select", new CharacterSelectScene());
    game.AddNewScene("start", new StartScene());
    game.AddNewScene("scoreboard-scene", new ScoreBoardScene());

    game.Start("start", 60, 1600, 832);
    return 0;
}
