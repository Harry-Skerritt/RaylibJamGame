//
// Created by Harry Skerritt on 06/07/2026.
//

#ifndef GAME_H
#define GAME_H
#include "Spawner.h"
#include "../Grid/Grid.h"
#include "../UI/Hotbar/Hotbar.h"

struct Coord {
    int q, r;

    bool operator==(const Coord& other) const {
        return q == other.q && r == other.r;
    }
};

class Game {
public:
    Game();
    ~Game();

    void update();
    void draw();


    void drawTilePlacement();
    void drawUI();

    void performMergeCheck(const Tile* tile);
    bool canMerge();

    void checkSacrificeMilestone(int new_max);

    int num = 1;

    [[nodiscard]] bool isPlacing() const { return is_placing; }

    // Game Win / Lose
    [[nodiscard]] bool isGameOver() const { return game_over; }

    [[nodiscard]] int getScore() const { return score; }
    [[nodiscard]] int getUnlocked() const { return m_spawner.getMaxAtomicNumber(); }
    [[nodiscard]] int sacrificeCount() const { return num_sacrifice; }

    // Reset
    void reset();
    void removeTiles(int amt);

private:
    Grid m_grid;
    Hotbar m_hotbar;
    Spawner m_spawner;

    Vector2 grid_pos = { 360.0f, 310.0f };
    Vector2 grid_sacrifice_pos = { 360.0f, 360.0f };

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
    float spawn_interval = 1.0f; // Seconds

    // States
    bool game_over = false;

    void shiftHotbar();
    void checkMouse();
    void increaseTileNumber(int q, int r, int amt);

};



#endif //GAME_H
