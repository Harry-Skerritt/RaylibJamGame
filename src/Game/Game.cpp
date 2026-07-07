//
// Created by Harry Skerritt on 06/07/2026.
//

#include "Game.h"
#include "raylib.h"
#include "../Grid/Tile.h"
#include <cmath>

Game::Game(): m_grid() {

}


void Game::update() {
    m_grid.update();

    is_placing = m_hotbar.isSlotOccupied(0);

    if (IsKeyPressed(KEY_ONE)) {
        m_hotbar.setSlot(0, num++);
        m_hotbar.setSlot(1, num++);
        m_hotbar.setSlot(2, num++);
    }


    if (is_placing && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Tile* tile = m_grid.getTileAtMouse();

        if (tile && tile->isValidPlacement()) {
            m_grid.setTile(tile->q, tile->r, m_hotbar.getSlot(0));
            shiftHotbar();
        }

    }
}

void Game::draw() {
    m_grid.draw(is_placing);
    drawTilePlacement();
}

void Game::drawUI() {
    m_hotbar.drawHotbar();
}

void Game::drawTilePlacement() {
    if (!is_placing) return;

    Tile* temp_tile = m_grid.getTileAtMouse();

    if (temp_tile != nullptr && temp_tile->atomic_number <= 0) {
        temp_tile->drawTempTile(temp_tile->pos, m_grid.getHexSize() - 10, m_hotbar.getSlot(0));
    }
}


// Private
void Game::shiftHotbar() {
    for (int i = 0; i < m_hotbar.getSlotCount(); i++) {
        if (m_hotbar.isSlotOccupied(i + 1)) {
            m_hotbar.setSlot(i, m_hotbar.getSlot(i + 1));
        } else {
            m_hotbar.clearSlot(i);
        }
    }

    m_hotbar.clearSlot(2);
    is_placing = false;
}






