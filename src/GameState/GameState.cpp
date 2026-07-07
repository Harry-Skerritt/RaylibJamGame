//
// Created by Harry Skerritt on 06/07/2026.
//

#include "GameState.h"

GameState::GameState() : menu(), game() {}

void GameState::update() {
    if (current_state == State::MENU) {
        menu.update();
        if (menu.shouldStartGame()) {
            current_state = State::PLAYING;
        }

    } else if (current_state == State::PLAYING) {
        game.update();
    } else if (current_state == State::GAMEOVER) {

    }
}

void GameState::draw() {
    if (current_state == State::MENU) {
        menu.draw();
    } else if (current_state == State::PLAYING) {
        game.draw();
    } else if (current_state == State::GAMEOVER) {

    }
}

void GameState::drawUI() {
    if (current_state == State::PLAYING) {
        game.drawUI();
    }
}
