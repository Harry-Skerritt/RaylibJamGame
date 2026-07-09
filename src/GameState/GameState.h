//
// Created by Harry Skerritt on 06/07/2026.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "../Menu/Menu.h"
#include "../Game/Game.h"
#include "../GameOver/GameOver.h"

enum class State { MENU, PLAYING, GAMEOVER };

class GameState {
public:
    GameState();

    State current_state = State::PLAYING; // Change to menu for prod

    Menu menu;
    Game game;
    GameOver game_over;

    void update();
    void draw();
    void drawUI();
};

#endif //GAMESTATE_H
