//
// Created by Harry Skerritt on 09/07/2026.
//

#include "Button.h"
#include "../../AssetManager/AssetManager.h"

Button::Button(const Texture2D &texture, const Vector2 position, const Vector2 size, const char* text, const int frames)
    : btn_texture(texture), btn_pos(position), btn_size(size), btn_frames(frames), btn_text(text)
{
    // Reset
    btn_state = 0;
    btn_action = false;

    frame_height = static_cast<float>(btn_texture.height) / btn_frames;
    btn_rect = { 0, 0, static_cast<float>(btn_texture.width), frame_height };

    btn_bounds = { btn_pos.x, btn_pos.y, btn_size.x, btn_size.y };

    btn_font = AssetManager::GetFont("iceland-50");
}

void Button::update(const char* new_text) {
    btn_action = false;

    if (new_text != "") btn_text = new_text;

    if (CheckCollisionPointRec(GetMousePosition(), btn_bounds)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btn_state = 2;
        else btn_state = 1;

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btn_action = true;
    }
    else btn_state = 0;

    btn_rect.y = btn_state * frame_height;
}

void Button::draw() {
    DrawTexturePro(btn_texture, btn_rect, btn_bounds, { 0, 0 }, 0.0f, WHITE);

    auto [x, y] = MeasureTextEx(btn_font, btn_text, 50, 2);
    const float text_x = btn_pos.x + (btn_size.x / 2.0f) - (x / 2.0f);
    const float text_y = btn_pos.y + (btn_size.y / 2.0f) - (y / 2.0f);
    DrawTextEx(btn_font, btn_text, {text_x , text_y}, 50, 2, WHITE);
}


