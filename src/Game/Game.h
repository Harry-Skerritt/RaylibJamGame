//
// Created by Harry Skerritt on 06/07/2026.
//

#ifndef GAME_H
#define GAME_H
#include "../Grid/Grid.h"


class Game {
public:
    Game();
    void update();
    void draw();


private:
    Grid m_grid;
};



#endif //GAME_H
