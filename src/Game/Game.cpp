//
// Created by Harry Skerritt on 06/07/2026.
//

#include "Game.h"
#include "raylib.h"
#include <iostream>
#include <ostream>

#include "../Grid/Tile.h"
#include "../AssetManager/AssetManager.h"
#include "../AudioManager/AudioManager.h"
#include "../utils/Element.h"
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
    text_manager.update(GetFrameTime());
    achievement_manager.update(GetFrameTime());

    if (IsKeyDown(KEY_A)) {
        achievement_manager.add("Transition Metals Complete", TRANSITION_METAL);
        AudioManager::PlaySFX("achievement");
    }

    handleSpawning();
    handlePlacing();
    handleCatalysts();
    handleStateTransitions();
}

void Game::draw() {
    if (sacrifice_mode) {
        m_grid.draw(is_placing, grid_sacrifice_pos);
        return;
    }

    m_grid.draw(is_placing, grid_pos);

    if (is_pulsing) {
        DrawRing(
            pulse_origin, pulse_radius, pulse_radius + 5.0f,
            0, 360, 30, Fade(GOLD, 1.0f - (pulse_radius / 150.0f)));
    }

    drawTilePlacement();
    text_manager.draw(AssetManager::GetFont("itim-25"));
    achievement_manager.draw(AssetManager::GetFont("iceland-20"), AssetManager::GetFont("itim-25"));
}

void Game::drawUI() {
    // Draw Hotbar
    if (!sacrifice_mode)
        m_hotbar.drawHotbar();

    // Draw Sacrifice Icon
    Vector2 sacrifice_pos = sacrifice_mode ? (Vector2){ 50.0f, 80.0f } : (Vector2){ 50.0f, 50.0f };
    sacrifice_icon.draw( sacrifice_pos, AssetManager::GetTexture("sacrifice-icon"), "E", num_sacrifice, (has_sacrifice));

    // Draw Main UI
    m_ui.draw(
        { 10, (float)GetScreenHeight() - 90 },
        { 265, 80 },
        score, getMaxAtomicNumber()
    );


    // Draw Sacrifice Mode Stuff
    if (sacrifice_mode) drawSacrificeOverlay();
}

// Game Over
void Game::reset() {
    // Reset Vars
    score = 0;
    sacrifice_mode = false;
    spawn_timer = 0.0f;
    num_sacrifice = 0;
    has_sacrifice = false;
    current_max = 0;

    // Reset Grid
    m_grid.reset();

    // Reset Spawner
    m_spawner.reset();

    m_hotbar.clearAll();
    m_hotbar.setSlot(0, 1);

    game_over = false;
    game_won = false;
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

    num_sacrifice = 0;
    has_sacrifice = false;
    game_over = false;
}


// ----- PRIVATE -----
// --- Logic Functions ---
void Game::checkSacrificeMilestone(const int new_max) {
    if (new_max > current_max) {
        int last_bucket = current_max / earn_sacrifice_amt;
        int curr_bucket = new_max / earn_sacrifice_amt;

        int crossed = curr_bucket - last_bucket;

        if (crossed > 0) {
            num_sacrifice += crossed;
            AudioManager::PlaySFX("sacrifice-added");
        }
        current_max = new_max;
    }

    has_sacrifice = (num_sacrifice >= 1);
}

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
            AudioManager::PlaySFX("tile-remove");
        }
        num_sacrifice -= 1;
        if (num_sacrifice <= 0) {
            has_sacrifice = false;
            sacrifice_mode = false;
        }
        return;
    }

    if (!is_placing) return;
    placeTile(tile);
}


// --- Logic Functions - Tiles ---
void Game::placeTile(Tile* tile) {
    if (!tile || !tile->isValidPlacement()) return;

    // Placing
    m_grid.setTile(tile->q, tile->r, m_hotbar.getSlot(0));
    progress_tracker.trackElement(m_hotbar.getSlot(0));

    for (int i = 0; i < 6; i++) {
        Tile* n = m_grid.getNeighbour(tile->q, tile->r, i);
        if (n && n->is_volatile) {
            catalyst_queue.push(n);
            m_grid.setTile(n->q, n->r, 0);
        }
    }

    AudioManager::PlaySFX("tile-place");

    // Score + Hotbar
    score += m_hotbar.getSlot(0);
    text_manager.add("+" + std::to_string(m_hotbar.getSlot(0)), tile->pos);
    shiftHotbar();

    // Merging
    performMergeCheck(tile);

    // Stability
    m_grid.updateStability(tile);
}

void Game::increaseTileNumber(const int q, const int r, const int amt) {
    Tile* tile = m_grid.getTile(q, r);
    if (!tile) return;

    int new_atomic_number = tile->atomic_number + amt;
    m_grid.setTile(tile->q, tile->r, new_atomic_number);
    progress_tracker.trackElement(new_atomic_number);

    ElementType type = PeriodicTable[new_atomic_number].type;
    if (progress_tracker.checkJustCompleted(type)) {
        std::string group_name = getTypePluralString(type);
        achievement_manager.add(group_name + " Complete!", type);
        AudioManager::PlaySFX("achievement");
    }

    m_spawner.setMaxAtomicNumber(new_atomic_number);
    checkSacrificeMilestone(new_atomic_number);
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
    text_manager.add("+" + std::to_string(10 * upgradeAmount), tile->pos);

    for (const auto* neighbor : matches) {
        AudioManager::PlaySFX("merge");
        m_grid.setTile(neighbor->q, neighbor->r, 0);
    }

    Tile* upgraded_tile = m_grid.getTile(q, r);
    performMergeCheck(upgraded_tile);
}

void Game::performCatalystExplosion(Tile *tile) {
    AudioManager::PlaySFX("catalyst");
    pulse_origin = tile->pos;
    is_pulsing = true;
    pulse_radius = 0.0f;
    m_grid.setTile(tile->q, tile->r, 0);

    for (int i = 0; i < 6; i++) {
        Tile* n = m_grid.getNeighbour(tile->q, tile->r, i);
        if (!n || n->atomic_number <= 0) continue;

        if (n->is_volatile) {
            catalyst_queue.push(n);
            m_grid.setTile(n->q, n->r, 0);
        } else {
            increaseTileNumber(n->q, n->r, 1);
            Tile* updated_n = m_grid.getTile(n->q, n->r);
            performMergeCheck(updated_n);
        }
    };
}

// --- Update Functions ---
void Game::handlePlacing() {
    // Placing
    is_placing = m_hotbar.isSlotOccupied(0);
    checkMouse();

}

void Game::handleCatalysts() {
    static int frame_counter = 0;
    if (!catalyst_queue.empty() && frame_counter++ % 5 == 0) { // Every 5 frames
        Tile* next = catalyst_queue.front();
        catalyst_queue.pop();
        performCatalystExplosion(next);
    }

    if (is_pulsing) {
        pulse_radius += 4.0f;
        if (pulse_radius > 150.0f) {
            is_pulsing = false;
        }
    }
}

void Game::handleSpawning() {
    // Auto Generate Elements
    spawn_timer += GetFrameTime();
    if (spawn_timer >= spawn_interval) {
        auto next_slot = m_hotbar.getNextEmptyIndex();

        if (next_slot != -1) {
            m_hotbar.setSlot(next_slot, m_spawner.spawnRandomElement(&m_grid));
        }

        spawn_timer = 0.0f;
    }
}

void Game::handleStateTransitions() {
    // Progress Screen
    go_to_progress = false;
    if (IsKeyPressed(KEY_TAB)) {
        go_to_progress = true;
    }

    // Sacrifice Mode
    if (IsKeyPressed(KEY_E)) {
        if (has_sacrifice) {
            sacrifice_mode = !sacrifice_mode;
            if (sacrifice_mode) AudioManager::PlaySFX("sacrifice-mode");
        }
    }

    // Game Lost
    if (m_grid.getEmptyTiles() == 0) {
        AudioManager::PlaySFX("game-over");
        game_over = true;
    }

    // Game Won
    if (m_spawner.getMaxAtomicNumber() == ELEMENT_COUNT) {
        AudioManager::PlaySFX("game-win");
        game_won = true;
    }
}

// --- Draw Functions ---
void Game::drawSacrificeOverlay() {
    auto sm_font = AssetManager::GetFont("itim-40");
    auto sm_x = Utils::getCentredTextPosEx("SACRIFICE_MODE", 40, &sm_font, 2);
    float pulse = (std::sin(GetTime() * 4.0f) * 0.5f) + 0.5f;

    Rectangle sm_background = {0, 0, (float)GetScreenWidth(), 100 };

    DrawRectangleGradientEx(sm_background, BLACK, Fade(BLACK, 0.0f), Fade(BLACK, 0.0f), BLACK);

    DrawTextEx(sm_font, "SACRIFICE MODE", { (float)sm_x, 20 }, 40, 2, RED);

    DrawRectangleLinesEx({0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
                        8, Fade(RED, pulse));
}

void Game::drawTilePlacement() {
    if (!is_placing) return;

    Tile* temp_tile = m_grid.getTileAtMouse();

    if (temp_tile != nullptr && temp_tile->atomic_number <= 0) {
        temp_tile->drawTempTile(temp_tile->pos, m_grid.getHexSize() - 10, m_hotbar.getSlot(0));
    }
}
