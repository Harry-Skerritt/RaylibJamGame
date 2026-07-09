//
// Created by Harry Skerritt on 06/07/2026.
//

#include "Game.h"
#include "raylib.h"
#include <iostream>
#include <ostream>

#include "../Grid/Tile.h"
#include "../AssetManager/AssetManager.h"
#include "../utils/TextUtils.h"

Game::Game()
    : m_grid(), m_spawner()
{
    m_hotbar.setSlot(0, 1);
}

Game::~Game() {
}

void Game::update() {
    m_grid.update();

    // Auto Generate Elements
    spawn_timer += GetFrameTime();
    if (spawn_timer >= spawn_interval) {
        auto next_slot = m_hotbar.getNextEmptyIndex();

        if (next_slot != -1) {
            m_hotbar.setSlot(next_slot, m_spawner.spawnRandomElement());
        }

        spawn_timer = 0.0f;
    }

    // Sacrifice Mode
    if (IsKeyPressed(KEY_E)) {
        if (has_sacrifice) {
            sacrifice_mode = !sacrifice_mode;
        }
    }

    is_placing = m_hotbar.isSlotOccupied(0);
    checkMouse();

    if (m_grid.getEmptyTiles() == 0) {
        std::cout << "GAME OVER" << std::endl;
        game_over = true;
    }

    if (IsKeyPressed(KEY_O)) {
        game_over = true;
    }
}

void Game::draw() {
    if (sacrifice_mode) {
        m_grid.draw(is_placing, grid_sacrifice_pos);
        return;
    }

    m_grid.draw(is_placing, grid_pos);
    drawTilePlacement();
}

void Game::drawUI() {
    // Draw Hotbar
    if (!sacrifice_mode)
        m_hotbar.drawHotbar();

    // Draw 'Stats'
    auto ui_font = AssetManager::GetFont("itim-25");
    const int font_size = 25;
    const int text_gap = 10;
    float current_y = (float)GetScreenHeight() - font_size - text_gap;

    std::string score_str = "Score: " + std::to_string(score);
    std::string highest_str = "Highest Atomic No: " + std::to_string(m_spawner.getMaxAtomicNumber());
    std::string sacrifice_count = "Sacrifice Available (" + std::to_string(num_sacrifice) + ") [E]";
    std::string sacrifice_str = has_sacrifice ?  sacrifice_count : "Sacrifice Unavailable";

    auto drawLine = [&](const std::string& text, Color color) {
        DrawTextEx(ui_font, text.c_str(), { (float)text_gap, current_y }, font_size, 2, color);
        current_y -= (font_size + text_gap);
    };

    drawLine(sacrifice_str, has_sacrifice ? GREEN : RED);
    drawLine(highest_str, RAYWHITE);
    drawLine(score_str, RAYWHITE);

    // Draw Sacrifice Stuff
    if (sacrifice_mode) {
        auto sm_font = AssetManager::GetFont("itim-40");
        auto sm_x = Utils::getCentredTextPosEx("SACRIFICE_MODE", 40, &sm_font, 2);

        Rectangle sm_background = {0, 0, (float)GetScreenWidth(), 100 };

        DrawRectangleGradientEx(sm_background, BLACK, Fade(BLACK, 0.0f), Fade(BLACK, 0.0f), BLACK);

        DrawTextEx(sm_font, "SACRIFICE MODE", { (float)sm_x, 20 }, 40, 2, RED);
    }
}

void Game::drawTilePlacement() {
    if (!is_placing) return;

    Tile* temp_tile = m_grid.getTileAtMouse();

    if (temp_tile != nullptr && temp_tile->atomic_number <= 0) {
        temp_tile->drawTempTile(temp_tile->pos, m_grid.getHexSize() - 10, m_hotbar.getSlot(0));
    }
}

void Game::performMergeCheck(const Tile* tile) {
    if (!tile) return;

    const int q = tile->q;
    const int r = tile->r;

    std::vector<Tile*> matches;

    for (int i = 0; i < 6; i++) {
        const auto n = m_grid.getNeighbour(static_cast<float>(tile->q), static_cast<float>(tile->r), i);
        if (n && n->atomic_number == tile->atomic_number) {
            matches.push_back(n);
        }
    }

    if (matches.empty()) return;

    const int upgradeAmount = static_cast<int>(matches.size());
    increaseTileNumber(q, r, upgradeAmount);
    score += (10 * upgradeAmount);

    for (const auto* neighbor : matches) {
        m_grid.setTile(neighbor->q, neighbor->r, 0);
    }

    Tile* upgraded_tile = m_grid.getTile(q, r);
    performMergeCheck(upgraded_tile);
}

void Game::checkSacrificeMilestone(const int new_max) {
    if (new_max > current_max) {
        int last_bucket = current_max / earn_sacrifice_amt;
        int curr_bucket = new_max / earn_sacrifice_amt;

        int crossed = curr_bucket - last_bucket;

        if (crossed > 0) {
            num_sacrifice += crossed;
        }
        current_max = new_max;
    }

    has_sacrifice = (num_sacrifice >= 1);
}

// Game Over
void Game::reset() {
    // Reset Vars
    score = 0;
    sacrifice_mode = false;
    spawn_timer = 0.0f;
    num_sacrifice = 0;
    has_sacrifice = false;

    // Reset Grid
    m_grid.reset();

    // Reset Spawner
    m_spawner.reset();

    m_hotbar.clearAll();
    m_hotbar.setSlot(0, 1);

    game_over = false;
}

void Game::removeTiles(int amt) {
    std::vector<Coord> cleared;

    for (int i = 0; i < amt; i++) {
        int q = GetRandomValue(-3, 3);
        int r = GetRandomValue(-3, 3);
        Coord new_coord = { q, r };

        if (std::find(cleared.begin(), cleared.end(), new_coord) == cleared.end()) {
            cleared.push_back(new_coord);
            m_grid.setTile(q, r, 0);
        }
    }

    game_over = false;
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

void Game::checkMouse() {
    if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) return;

    Tile* tile = m_grid.getTileAtMouse();

    if (sacrifice_mode) {
        if (tile && tile->atomic_number > 0) {
            m_grid.setTile(tile->q, tile->r, 0);
        }
        num_sacrifice -= 1;
        if (num_sacrifice <= 0) {
            has_sacrifice = false;
            sacrifice_mode = false;
        }
        return;
    }

    if (is_placing) {
        if (tile && tile->isValidPlacement()) {
            m_grid.setTile(tile->q, tile->r, m_hotbar.getSlot(0));
            // Temp
            score += m_hotbar.getSlot(0);
            // ---
            shiftHotbar();
        }

        performMergeCheck(tile);
        return;
    }
}

void Game::increaseTileNumber(const int q, const int r, const int amt) {
    Tile* tile = m_grid.getTile(q, r);
    if (!tile) return;

    int new_atomic_number = tile->atomic_number + amt;
    m_grid.setTile(tile->q, tile->r, new_atomic_number);
    m_spawner.setMaxAtomicNumber(new_atomic_number);

    checkSacrificeMilestone(new_atomic_number);
}







