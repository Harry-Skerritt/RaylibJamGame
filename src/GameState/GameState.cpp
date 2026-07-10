//
// Created by Harry Skerritt on 06/07/2026.
//

#include "GameState.h"

#include <iostream>
#include <__ostream/basic_ostream.h>

#include "../AssetManager/AssetManager.h"

GameState::GameState() : menu(), game(), game_over(), curr_music(), progress() {
    swapMusic("menu-music");
}


void GameState::update() {
    if (curr_music != nullptr) {
        UpdateMusicStream(*curr_music);
    }

    if (current_state == State::MENU) {
        menu.update();
        if (menu.shouldStartGame()) {
            if (curr_music != nullptr) StopMusicStream(*curr_music);

            menu.reset();
            swapMusic("main-music");
            current_state = State::PLAYING;
        }
    }
    else if (current_state == State::PLAYING) {
        game.update();

        if (game.isGameOver()) {
            game_over.init(&game);
            current_state = State::GAME_OVER;
        }

        if (game.isGameWon()) {
            game_win.init();
            current_state = State::GAME_WIN;
        }

        if (game.goToProgress()) {
            progress.init(game.getMaxAtomicNumber());
            current_state = State::PROGRESS;
        }
    }
    else if (current_state == State::GAME_OVER) {
        game_over.update();

        int result_state = game_over.getResultState();
        switch (result_state) {
            case(0):
                // Quit
                game.reset();
                swapMusic("menu-music");
                current_state = State::MENU;
                break;

            case(1):
                // Restart
                game.reset();
                current_state = State::PLAYING;
                break;

            case(2):
                // Continue
                game.removeTiles(game.sacrificeCount());
                current_state = State::PLAYING;
                break;
        }
    }
    else if (current_state == State::GAME_WIN) {
        game_win.update();

        int result_state = game_win.getResultState();
        switch (result_state) {
            case(0):
                // Quit
                game.reset();
                swapMusic("menu-music");
                current_state = State::MENU;
                break;

            case(1):
                // Restart
                game.reset();
                current_state = State::PLAYING;
                break;
        }
    }
    else if (current_state == State::PROGRESS) {
        if (progress.transitionToGame()) {
            current_state = State::PLAYING;
        }
        progress.update();
    }
}

void GameState::draw() {
    if (current_state == State::MENU) {
        menu.draw();
    }
    else if (current_state == State::PLAYING) {
        game.draw();
    }
    else if (current_state == State::GAME_OVER) {
        game_over.draw();
    }
    else if (current_state == State::GAME_WIN) {
        game_win.draw();
    }
    else if (current_state == State::PROGRESS) {
        progress.draw();
    }
}

void GameState::drawUI() {
    if (current_state == State::PLAYING) {
        game.drawUI();
    }
}

void GameState::swapMusic(const std::string &new_music) {
    if (curr_music != nullptr) StopMusicStream(*curr_music);
    curr_music = &AssetManager::GetMusic(new_music);
    PlayMusicStream(*curr_music);
    SetMusicVolume(*curr_music, 0.3f); // 0.3f
}

