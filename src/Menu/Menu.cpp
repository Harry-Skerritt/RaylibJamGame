//
// Created by Harry Skerritt on 06/07/2026.
//

#include "Menu.h"
#include "raylib.h"
#include <iostream>

#include "../AssetManager/AssetManager.h"
#include "../AudioManager/AudioManager.h"
#include "../utils/Colours.h"
#include "../utils/TextUtils.h"

Menu::Menu() {
    background_atom = AssetManager::GetTexture("atom");
    createBackground();
    createButtons();
}

Menu::~Menu() {}

void Menu::update() {
    if (IsKeyPressed(KEY_ENTER)) {
        AudioManager::PlaySFX("game-start");
        start_game = true;
        std::cout << "Enter Pressed" << std::endl;
    }

    updateBackground();
    updateButtons();
}

void Menu::draw() {
    drawBackground();
    drawLogo();
    drawStart();

    music_button->draw();
    sfx_button->draw();
}


// PRIVATE
void Menu::drawLogo() {
    auto title_texture = AssetManager::GetTexture("menu-title");
    int x_pos = (GetScreenWidth() - title_texture.width) / 2;
    int y_pos = 30;

    DrawTexture(title_texture, x_pos, y_pos, WHITE);
}

void Menu::drawStart() {
    auto font = AssetManager::GetFont("itim-40");
    const char* start_text = "PRESS ENTER TO START";
    constexpr int start_size = 40;
    constexpr int font_spacing = 2;

    Vector2 text_pos = {
        (float)Utils::getCentredTextPosEx(start_text, start_size, &font, font_spacing),
        400.0f
    };

    if (static_cast<int>(GetTime() * 2) % 2 == 0) {
        DrawTextEx(font, start_text, text_pos, start_size, font_spacing, Colours::TEXT_COLOUR);
    }
}

// Background
void Menu::createBackground() {
    for (int i = 0; i < 20; i++) {
        BackgroundAtom atom;
        atom.pos = { (float)GetRandomValue(0, 720), (float)GetRandomValue(0, 720) };

        atom.velocity = { (float)GetRandomValue(-50, 50), (float)GetRandomValue(-50, 50) };
        atom.rotation = (float)GetRandomValue(0, 360);
        atom.rotation_speed = (float)GetRandomValue(-40, 40);
        background_atoms.push_back(atom);
    }
}

void Menu::updateBackground() {
    for (auto& atom : background_atoms) {
        atom.rotation += atom.rotation_speed * GetFrameTime();

        atom.pos.x += atom.velocity.x * GetFrameTime();
        atom.pos.y += atom.velocity.y * GetFrameTime();

        // Screen Wrap
        if (atom.pos.x < -50) atom.pos.x = GetScreenWidth() + 50;
        if (atom.pos.x > GetScreenWidth() + 50) atom.pos.x = -50;
        if (atom.pos.y < -50) atom.pos.y = GetScreenHeight() + 50;
        if (atom.pos.y > GetScreenHeight() + 50) atom.pos.y = -50;
    }
}

void Menu::drawBackground() {
    Rectangle source = { 0, 0, static_cast<float>(background_atom.width), static_cast<float>(background_atom.height) };

    Vector2 origin = { static_cast<float>(background_atom.width) / 8, static_cast<float>(background_atom.height) / 8 };

    for (auto& atom : background_atoms) {
        Rectangle dest = {
            atom.pos.x,
            atom.pos.y,
            static_cast<float>(background_atom.width) / 4,
            static_cast<float>(background_atom.height) / 4
        };

        DrawTexturePro(background_atom, source, dest, origin, atom.rotation, WHITE);
    }
}

// Buttons
void Menu::createButtons() {
    music_button = new Button(AssetManager::GetTexture("small-btn"),
       { static_cast<float>(GetScreenWidth()) / 2.0f - 320.0f, 530 },  { 300, 55}, music_str);

    sfx_button = new Button(AssetManager::GetTexture("small-btn"),
        { static_cast<float>(GetScreenWidth()) / 2.0f + 20.0f, 530 }, { 300, 55 }, sfx_str);
}

void Menu::updateButtons() {
    if (AudioManager::IsMusicEnabled()) music_str = "MUSIC ON";
    else music_str = "MUSIC OFF";

    if (AudioManager::IsSFXEnabled()) sfx_str = "SFX ON";
    else sfx_str = "SFX OFF";

    music_button->update(music_str);
    sfx_button->update(sfx_str);


    if (music_button->isPressed()) {
        AudioManager::ToggleMusic();
        AudioManager::PlaySFX("btn-click");
    }

    if (sfx_button->isPressed()) {
        AudioManager::ToggleSFX();
        AudioManager::PlaySFX("btn-click");
    }
}

