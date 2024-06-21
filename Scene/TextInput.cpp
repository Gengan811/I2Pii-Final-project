#include <allegro5/allegro_font.h>
#include "TextInput.hpp"
#include "Engine/Resources.hpp"
#include <allegro5/allegro_primitives.h>

TextInput::TextInput(float x, float y, float w, float h) : Engine::IObject(x, y), width(w), height(h) {
    text = "";
}

void TextInput::Draw() const {
    al_draw_filled_rectangle(Position.x, Position.y, Position.x + width, Position.y + height, al_map_rgb(255, 255, 255));
    al_draw_rectangle(Position.x, Position.y, Position.x + width, Position.y + height, al_map_rgb(0, 0, 0), 2);
    //al_draw_text((const ALLEGRO_FONT *) Engine::Resources::GetInstance().GetFont("pirulen.ttf", 48), al_map_rgb(0, 0, 0), Position.x + 5, Position.y + 5, 0, text.c_str());
    //al_draw_text(font.get(), Color, Position.x - Anchor.x * GetTextWidth(), Position.y - Anchor.y * GetTextHeight(), 0, Text.c_str());
}

void TextInput::OnKeyDown(int keycode) {
    if (keycode == ALLEGRO_KEY_ENTER) {
        if (OnSubmit) {
            OnSubmit(text);
        }
    }
}

void TextInput::OnKeyChar(int keycode) {
    if (keycode == ALLEGRO_KEY_BACKSPACE) {
        if (!text.empty()) {
            text.pop_back();
        }
    } else {
        char input = static_cast<char>(keycode);
        if (isalnum(input) || isspace(input)) {
            text += input;
        }
    }
}

void TextInput::SetText(const std::string& text) {
    this->text = text;
}

std::string TextInput::GetText() const {
    return text;
}
