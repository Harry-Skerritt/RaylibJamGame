//
// Created by Harry Skerritt on 06/07/2026.
//

#include "Game.h"
#include "raylib.h"
#include <cmath>

Game::Game(): m_grid() {

}


void Game::update() {
    m_grid.update();
}

void Game::draw() {
    m_grid.draw();
}





