//
// Created by Harry Skerritt on 09/07/2026.
//

#include "GameOver.h"
#include "../AssetManager/AssetManager.h"
#include "../utils/Element.h"
#include <iostream>

GameOver::GameOver()
    : score(0), unlock_count(0), total_count(0), sacrifice_count(0), btn_sound() {
}

GameOver::~GameOver() {
    delete quit_button;
    delete restart_button;
    delete continue_button;
}

void GameOver::init(const Game *game) {
    score = game->getScore();
    unlock_count = game->getUnlocked();
    sacrifice_count = game->sacrificeCount();
    total_count = ELEMENT_COUNT;

    quit_button = new Button(AssetManager::GetTexture("small-btn"),
        { static_cast<float>(GetScreenWidth()) / 2.0f - 200.0f, 615 },  { 400, 65}, "QUIT TO MENU");

    restart_button = new Button(AssetManager::GetTexture("small-btn"),
        { static_cast<float>(GetScreenWidth()) / 2.0f - 200.0f, 530 }, { 400, 65 }, "RESTART");

    continue_button = new Button(AssetManager::GetTexture("small-btn"),
        { static_cast<float>(GetScreenWidth()) / 2.0f - 200.0f, 445 }, { 400, 65 }, "CONTINUE");


    can_continue = (sacrifice_count >= 1);

    result_state = -1;

    btn_sound = AssetManager::GetSound("btn-click");
}

void GameOver::update() {
    quit_button->update();
    restart_button->update();
    continue_button->update();

    if (quit_button->isPressed()) {
        PlaySound(btn_sound);
        result_state = 0;
    }

    if (restart_button->isPressed()) {
        PlaySound(btn_sound);
        result_state = 1;
    }

    if (continue_button->isPressed()) {
        PlaySound(btn_sound);
        result_state = 2;
    }
}


void GameOver::draw() {
    // Draw Background Texture
    auto atom_texture = AssetManager::GetTexture("atom");
    DrawTexture(atom_texture,
        GetScreenWidth() / 2 - atom_texture.width / 2,
        GetScreenHeight() / 2 - atom_texture.height / 2,
        WHITE);


    // Draw Game over Text
    auto game_over_font = AssetManager::GetFont("iceland-100");
    auto game_over_text = "GAME OVER";
    auto game_over_size = MeasureTextEx(game_over_font, game_over_text, 100, 2);

    DrawTextEx(game_over_font, game_over_text,
        { GetScreenWidth() / 2 - game_over_size.x / 2, 50 },
        100, 2, WHITE);


    // Draw Meta Text
    auto meta_font = AssetManager::GetFont("iceland-50");

    // Score
    auto score_text = "Score: " + std::to_string(score);
    auto score_size = MeasureTextEx(meta_font, score_text.c_str(), 50, 2);
    DrawTextEx(meta_font, score_text.c_str(),
        { GetScreenWidth() / 2 - score_size.x / 2, 150},
        50, 2, WHITE);

    // Unlocked
    auto unlock_text = "You Unlocked: " + std::to_string(unlock_count) + " / " + std::to_string(total_count) + " Elements";
    auto unlock_size = MeasureTextEx(meta_font, unlock_text.c_str(), 50, 2);
    DrawTextEx(meta_font, unlock_text.c_str(),
        { GetScreenWidth() / 2 - unlock_size.x / 2, 200 },
        50, 2, WHITE);


    // Continue
    auto continue_font = AssetManager::GetFont("iceland-40");
    auto continue_text = "You can sacrifice " + std::to_string(sacrifice_count) + " pieces to continue";
    auto continue_size = MeasureTextEx(continue_font, continue_text.c_str(), 40, 2);
    if (can_continue) {
        DrawTextEx(continue_font, continue_text.c_str(),
            { GetScreenWidth() / 2 - continue_size.x / 2, 380 },
            40, 2, WHITE);
    }

    quit_button->draw();
    restart_button->draw();

    if (can_continue) continue_button->draw();
}




