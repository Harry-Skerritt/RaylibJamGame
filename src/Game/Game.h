//
// Created by Harry Skerritt on 06/07/2026.
//

#ifndef GAME_H
#define GAME_H
#include "Spawner.h"
#include "../Grid/Grid.h"
#include "../UI/Hotbar/Hotbar.h"
#include "../UI/Icon/Icon.h"
#include <queue>

#include "../UI/FloatingText/FloatingTextManager.h"
#include "../UI/UINum/UINum.h"

class Game {
public:
    Game();
    ~Game();

    void update();
    void draw();

    void drawTilePlacement();
    void drawUI();

    void performMergeCheck(const Tile* tile);
    void checkSacrificeMilestone(int new_max);

    [[nodiscard]] bool isPlacing() const { return is_placing; }

    // Game Win / Lose / Progress
    [[nodiscard]] bool isGameOver() const { return game_over; }
    [[nodiscard]] bool isGameWon() const { return game_won; }
    [[nodiscard]] bool goToProgress() const { return go_to_progress; }

    [[nodiscard]] int getScore() const { return score; }
    [[nodiscard]] int getUnlocked() const { return m_spawner.getMaxAtomicNumber(); }
    [[nodiscard]] int sacrificeCount() const { return num_sacrifice; }

    // Reset
    void reset();
    void removeTiles(int amt);

    int getMaxAtomicNumber() const { return m_spawner.getMaxAtomicNumber(); }

private:
    Grid m_grid;
    Hotbar m_hotbar;
    UINum m_ui;
    Spawner m_spawner;
    FloatingTextManager text_manager;

    Vector2 grid_pos = { 360.0f, 310.0f };
    Vector2 grid_sacrifice_pos = { 360.0f, 360.0f };

    // UI
    Icon sacrifice_icon;

    // Placing
    bool is_placing = false;

    // Sacrifice
    bool sacrifice_mode = false;
    bool has_sacrifice = false;
    int earn_sacrifice_amt = 10;
    int num_sacrifice = 0;
    int current_max = 0;

    // Score
    int score = 0;

    // Spawning
    float spawn_timer = 0.0f;
    float spawn_interval = 0.8f; // Seconds

    // States
    bool game_over = false;
    bool game_won = false;
    bool go_to_progress = false;

    // Catalyst
    float pulse_radius = 0.0f;
    bool is_pulsing = false;
    Vector2 pulse_origin = {0,0};
    std::queue<Tile*> catalyst_queue;
    void triggerCatalyst(Tile* tile);
    void performCatalystExplosion(Tile* tile);

    void shiftHotbar();
    void checkMouse();
    void increaseTileNumber(int q, int r, int amt);
    void placeTile(Tile* tile);
};



#endif //GAME_H
