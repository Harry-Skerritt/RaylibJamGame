//
// Created by Harry Skerritt on 06/07/2026.
//

#include "Game.h"
#include "raylib.h"
#include "../Grid/Tile.h"
#include <cmath>

#include "../AssetManager/AssetManager.h"

Game::Game(): m_grid() {

}

Game::~Game() {
}



void Game::update() {
    m_grid.update();

    if (IsKeyPressed(KEY_E)) {
        auto next_slot = m_hotbar.getNextEmptyIndex();
        if (next_slot == -1) return;
        m_hotbar.setSlot(next_slot, num++);
    }

    is_placing = m_hotbar.isSlotOccupied(0);

    if (is_placing && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Tile* tile = m_grid.getTileAtMouse();

        if (tile && tile->isValidPlacement()) {
            m_grid.setTile(tile->q, tile->r, m_hotbar.getSlot(0));
            // Temp
            score += m_hotbar.getSlot(0);
            updateHighestAtomicNumber(m_hotbar.getSlot(0));
            // ---
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

    auto ui_font = AssetManager::GetFont("itim-25");
    const int font_size = 25;
    const int text_gap = 10;
    float current_y = (float)GetScreenHeight() - font_size - text_gap;

    std::string score_str = "Score: " + std::to_string(score);
    std::string highest_str = "Highest Atomic No: " + std::to_string(highest_atomic_number);
    std::string sacrifice_str = has_sacrifice ? "Sacrifice Available" : "Sacrifice Unavailable";

    auto drawLine = [&](const std::string& text, Color color) {
        DrawTextEx(ui_font, text.c_str(), { (float)text_gap, current_y }, font_size, 2, color);
        current_y -= (font_size + text_gap);
    };

    drawLine(sacrifice_str, has_sacrifice ? GREEN : RED);
    drawLine(highest_str, RAYWHITE);
    drawLine(score_str, RAYWHITE);
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

void Game::updateHighestAtomicNumber(const int number) {
    if (number > highest_atomic_number) highest_atomic_number = number;
}







