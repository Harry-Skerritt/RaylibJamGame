//
// Created by Harry Skerritt on 06/07/2026.
//

#ifndef GAME_H
#define GAME_H
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

    int num = 1;

    bool isPlacing() const { return is_placing;}

private:
    Grid m_grid;
    Hotbar m_hotbar;

    bool is_placing = false;

    bool has_sacrifice = false;
    int score = 0;
    int highest_atomic_number = 0;

    void shiftHotbar();
    void updateHighestAtomicNumber(int number);

};



#endif //GAME_H
