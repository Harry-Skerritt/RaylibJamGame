//
// Created by Harry Skerritt on 06/07/2026.
//

#include "GameState.h"

#include <iostream>
#include <__ostream/basic_ostream.h>

GameState::GameState() : menu(), game(), game_over() {}

void GameState::update() {
    if (current_state == State::MENU) {
        menu.update();
        if (menu.shouldStartGame()) {
            current_state = State::PLAYING;
        }

    } else if (current_state == State::PLAYING) {
        game.update();

        if (game.isGameOver()) {
            game_over.init(&game);
            current_state = State::GAMEOVER;
        }
    } else if (current_state == State::GAMEOVER) {
        game_over.update();

        int result_state = game_over.getResultState();
        switch (result_state) {
            case(0):
                game.reset();
                current_state = State::MENU;
                break;

            case(1):
                game.reset();
                current_state = State::PLAYING;
                break;

            case(2):
                game.removeTiles(game.sacrificeCount());
                current_state = State::PLAYING;
                break;
        }
    }
}

void GameState::draw() {
    if (current_state == State::MENU) {
        menu.draw();
    } else if (current_state == State::PLAYING) {
        game.draw();
    } else if (current_state == State::GAMEOVER) {
        game_over.draw();
    }
}

void GameState::drawUI() {
    if (current_state == State::PLAYING) {
        game.drawUI();
    }
}
