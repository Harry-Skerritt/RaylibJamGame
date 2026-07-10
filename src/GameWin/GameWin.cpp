//
// Created by Harry Skerritt on 09/07/2026.
//

#include "GameWin.h"
#include "../AssetManager/AssetManager.h"
#include "raylib.h"
#include "../AudioManager/AudioManager.h"

GameWin::GameWin() {}

GameWin::~GameWin() {
    delete quit_button;
    delete restart_button;
}


void GameWin::init() {
    quit_button = new Button(AssetManager::GetTexture("small-btn"),
        { static_cast<float>(GetScreenWidth()) / 2.0f - 200.0f, 615 },  { 400, 65}, "QUIT TO MENU");

    restart_button = new Button(AssetManager::GetTexture("small-btn"),
        { static_cast<float>(GetScreenWidth()) / 2.0f - 200.0f, 530 }, { 400, 65 }, "RESTART");


    result_state = -1;
    btn_sound = AssetManager::GetSound("btn-click");
}

void GameWin::update() {
    quit_button->update();
    restart_button->update();

    if (quit_button->isPressed()) {
        AudioManager::PlaySFX("btn-click");
        result_state = 0;
    }

    if (restart_button->isPressed()) {
        AudioManager::PlaySFX("btn-click");
        result_state = 1;
    }
}

void GameWin::draw() {
    // Draw Background Texture
    auto atom_texture = AssetManager::GetTexture("atom");
    DrawTexture(atom_texture,
        GetScreenWidth() / 2 - atom_texture.width / 2,
        GetScreenHeight() / 2 - atom_texture.height / 2,
        WHITE);


    // Draw Game over Text
    auto game_over_font = AssetManager::GetFont("iceland-80");
    auto game_over_text = "GAME COMPLETE";
    auto game_over_size = MeasureTextEx(game_over_font, game_over_text, 80, 2);

    DrawTextEx(game_over_font, game_over_text,
            { GetScreenWidth() / 2 - game_over_size.x / 2, 50 },
            80, 2, WHITE);

    // Draw Meta Text
    auto meta_font = AssetManager::GetFont("iceland-40");

    auto unlock_text = "You Synthesised All The Elements!";
    auto unlock_size = MeasureTextEx(meta_font, unlock_text, 40, 2);
    DrawTextEx(meta_font, unlock_text,
        { GetScreenWidth() / 2 - unlock_size.x / 2, 200 },
        40, 2, WHITE);

    quit_button->draw();
    restart_button->draw();
}


