//
// Created by Harry Skerritt on 06/07/2026.
//

#include "Menu.h"
#include "raylib.h"
#include <iostream>

#include "../utils/TextUtils.h"

void Menu::update() {
    if (IsKeyPressed(KEY_ENTER)) {
        start_game = true;
        std::cout << "Enter Pressed" << std::endl;
    }
}

void Menu::draw() {
    const char* title_text = "ATOMIC SYNTHESIS";
    constexpr int title_size = 60;

    DrawText(title_text,
        Utils::getCentredTextPos(title_text, title_size), 150, title_size, DARKBLUE);

    const char* start_text = "PRESS ENTER TO START";
    constexpr int start_size = 25;
    if (static_cast<int>(GetTime() * 2) % 2 == 0) {
        DrawText(start_text,
            Utils::getCentredTextPos(start_text, start_size), 500, start_size, GRAY);
    }
}
