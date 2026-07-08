//
// Created by Harry Skerritt on 06/07/2026.
//

#include "Game.h"
#include "raylib.h"
#include "../Grid/Tile.h"
#include <cmath>
#include <iostream>
#include <ostream>

#include "../AssetManager/AssetManager.h"
#include "../utils/Element.h"

Game::Game()
    : m_grid(), m_spawner(sizeof(PeriodicTable) / sizeof(*PeriodicTable)) {}

Game::~Game() {
}



void Game::update() {
    m_grid.update();

    if (IsKeyPressed(KEY_E)) {
        auto next_slot = m_hotbar.getNextEmptyIndex();
        if (next_slot == -1) return;
        m_hotbar.setSlot(next_slot, m_spawner.spawnRandomElement());
    }

    if (IsKeyPressed(KEY_R)) {
        m_spawner.setMaxAtomicNumber(m_spawner.getMaxAtomicNumber() + 1);
    }

    is_placing = m_hotbar.isSlotOccupied(0);

    if (is_placing && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Tile* tile = m_grid.getTileAtMouse();

        if (tile && tile->isValidPlacement()) {
            m_grid.setTile(tile->q, tile->r, m_hotbar.getSlot(0));
            // Temp
            score += m_hotbar.getSlot(0);
            // ---
            shiftHotbar();
        }

        performMergeCheck(tile);

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
    std::string highest_str = "Highest Atomic No: " + std::to_string(m_spawner.getMaxAtomicNumber());
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

void Game::performMergeCheck(Tile* tile, const bool first_run) {

    for (int i = 0; i < 6; i++) {
        const auto n = m_grid.getNeighbour(tile->q, tile->r, i);
        if (n == nullptr) continue;

        if (n->atomic_number == tile->atomic_number) {
            // Up the placed tile
            const auto new_an = tile->atomic_number + 1;
            m_grid.setTile(tile->q, tile->r, new_an);
            m_spawner.setMaxAtomicNumber(new_an);

            // Increase Score
            // Todo: Figure out a value for this
            score += 1;

            // Remove old tile
            m_grid.setTile(n->q, n->r, 0);

            // Recheck
            // Todo: Change this to a count
            if (first_run) performMergeCheck(tile, false);
        }
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







