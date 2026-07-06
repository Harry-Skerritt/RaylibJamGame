//
// Created by Harry Skerritt on 06/07/2026.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "../Menu/Menu.h"

enum class State { MENU, PLAYING, GAMEOVER };

class GameState {
public:
    State current_state = State::MENU;
    Menu menu;
    void update();
    void draw();
};

#endif //GAMESTATE_H
