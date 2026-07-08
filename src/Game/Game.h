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

    int num = 1;

    bool isPlacing() const { return is_placing;}

private:
    Grid m_grid;
    Hotbar m_hotbar;
    Spawner m_spawner;

    bool is_placing = false;

    bool has_sacrifice = false;
    int score = 0;

    void shiftHotbar();

};



#endif //GAME_H
