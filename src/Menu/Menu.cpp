//
// Created by Harry Skerritt on 06/07/2026.
//

#include "Menu.h"
#include "raylib.h"
#include <iostream>

#include "../utils/Colours.h"
#include "../utils/TextUtils.h"

Menu::Menu() {
}

Menu::~Menu() {
    UnloadTexture(title_texture);
    UnloadFont(font);
}


void Menu::update() {
    if (IsKeyPressed(KEY_ENTER)) {
        start_game = true;
        std::cout << "Enter Pressed" << std::endl;
    }
}


void Menu::draw() {
    drawLogo();
    drawStart();
}


// PRIVATE
void Menu::initTexture() {
    title_texture = LoadTexture("resources/menu/title.png");
    std::cout << "Texture loaded" << std::endl;
    is_texture_loaded = true;
}

void Menu::initFont(float font_size) {
    font = LoadFontEx("resources/fonts/Iceland/Iceland-Regular.ttf", font_size, 0 , 0);
    std::cout << "Font loaded" << std::endl;
    is_font_loaded = true;
}

void Menu::drawLogo() {
    if (!is_texture_loaded) initTexture();

    int x_pos = (GetScreenWidth() - title_texture.width) / 2;
    int y_pos = 30;

    DrawTexture(title_texture, x_pos, y_pos, WHITE);
}

void Menu::drawStart() {
    const char* start_text = "PRESS ENTER TO START";
    constexpr int start_size = 40;
    constexpr int font_spacing = 2;

    if (!is_font_loaded) initFont(start_size);

    Vector2 text_pos = {
        (float)Utils::getCentredTextPosEx(start_text, start_size, &font, font_spacing),
        500.0f
    };

    if (static_cast<int>(GetTime() * 2) % 2 == 0) {
        DrawTextEx(font, start_text, text_pos, start_size, font_spacing, Colours::TEXT_COLOUR);
    }
}
