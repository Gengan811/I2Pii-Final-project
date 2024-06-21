#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_TEXTINPUT_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_TEXTINPUT_HPP
#include <allegro5/allegro_font.h>
#include <string>
#include <functional>
#include "Engine/IObject.hpp"

class TextInput : public Engine::IObject {
public:
    std::function<void(const std::string&)> OnSubmit;
    TextInput(float x, float y, float w, float h);
    void Draw() const override;
    void OnKeyDown(int keycode);
    void OnKeyChar(int keycode);
    void SetText(const std::string& text);
    std::string GetText() const;

private:
    std::string text;
    float width, height;
};


#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_TEXTINPUT_HPP
