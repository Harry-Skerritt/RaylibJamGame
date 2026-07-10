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

#include "../Progress/ProgressTracker.h"
#include "../UI/Achievement/AchievementManager.h"
#include "../UI/FloatingText/FloatingTextManager.h"
#include "../UI/UINum/UINum.h"

class Game {
public:
    Game();
    ~Game();

    void update();
    void draw();
    void drawUI();

    // Game Win / Lose / Progress
    [[nodiscard]] bool isGameOver() const { return game_over; }
    [[nodiscard]] bool isGameWon() const { return game_won; }
    [[nodiscard]] bool goToProgress() const { return go_to_progress; }

    // Getters
    [[nodiscard]] bool isPlacing() const { return is_placing; }
    [[nodiscard]] int getScore() const { return score; }
    [[nodiscard]] int getUnlocked() const { return m_spawner.getMaxAtomicNumber(); }
    [[nodiscard]] int sacrificeCount() const { return num_sacrifice; }
    int getMaxAtomicNumber() const { return m_spawner.getMaxAtomicNumber(); }

    ProgressLog getProgressLog() { return progress_tracker.getProgressLog(); }

    // Reset
    void reset();
    void removeTiles(int amt);

private:
    // Grid
    Grid m_grid;
    Vector2 grid_pos = { 360.0f, 310.0f };
    Vector2 grid_sacrifice_pos = { 360.0f, 360.0f };
    ProgressTracker progress_tracker;

    // Spawning
    float spawn_timer = 0.0f;
    float spawn_interval = 0.8f; // Seconds
    Spawner m_spawner;

    // UI
    Hotbar m_hotbar;
    UINum m_ui;
    FloatingTextManager text_manager;
    AchievementManager achievement_manager;
    Icon sacrifice_icon;

    // Tiles
    bool is_placing = false;

    // Catalyst
    float pulse_radius = 0.0f;
    bool is_pulsing = false;
    Vector2 pulse_origin = {0,0};
    std::queue<Tile*> catalyst_queue;

    // Sacrifice
    bool sacrifice_mode = false;
    bool has_sacrifice = false;
    int earn_sacrifice_amt = 10;
    int num_sacrifice = 0;
    int current_max = 0;

    // Score
    int score = 0;

    // States
    bool game_over = false;
    bool game_won = false;
    bool go_to_progress = false;


    // Update
    void handleStateTransitions();
    void handleSpawning();
    void handleCatalysts();
    void handlePlacing();

    // Draw
    void drawTilePlacement();
    void drawSacrificeOverlay();

    // Logic Functions
    void checkSacrificeMilestone(int new_max);
    void shiftHotbar();
    void checkMouse();

    // Logic Functions - Tiles
    void placeTile(Tile* tile);
    void increaseTileNumber(int q, int r, int amt);
    void performMergeCheck(const Tile* tile);
    void performCatalystExplosion(Tile* tile);

};


#endif //GAME_H
