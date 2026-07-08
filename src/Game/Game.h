//
// Created by Harry Skerritt on 06/07/2026.
//

#ifndef GAME_H
#define GAME_H
#include "Spawner.h"
#include "../Grid/Grid.h"
#include "../UI/Hotbar/Hotbar.h"


class Game {
public:
    Game();
    ~Game();

    void update();
    void draw();


    void drawTilePlacement();
    void drawUI();

    void performMergeCheck(Tile* tile,  bool first_run = true);
    void calcSacrifice();

    int num = 1;

    bool isPlacing() const { return is_placing;}

private:
    Grid m_grid;
    Hotbar m_hotbar;
    Spawner m_spawner;

    bool is_placing = false;

    bool sacrifice_mode = false;
    bool has_sacrifice = false;
    int earn_sacrifice_amt = 10;
    int num_sacrifice = 0;
    int score = 0;

    float spawn_timer = 0.0f;
    float spawn_interval = 2.0f; // Seconds

    Vector2 grid_pos = { 360.0f, 310.0f };
    Vector2 grid_sacrifice_pos = { 360.0f, 360.0f };

    void shiftHotbar();

    void checkMouse();

};



#endif //GAME_H
