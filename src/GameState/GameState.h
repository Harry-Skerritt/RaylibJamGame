//
// Created by Harry Skerritt on 06/07/2026.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "../Menu/Menu.h"
#include "../Game/Game.h"

enum class State { MENU, PLAYING, GAMEOVER };

class GameState {
public:
    GameState();

    State current_state = State::MENU;

    Menu menu;
    Game game;

    void update();
    void draw();
};

#endif //GAMESTATE_H
