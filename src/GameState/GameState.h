//
// Created by Harry Skerritt on 06/07/2026.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "../Menu/Menu.h"
#include "../Game/Game.h"
#include "../GameOver/GameOver.h"
#include "../GameWin/GameWin.h"

enum class State { MENU, PLAYING, GAMEOVER, GAMEWIN };

class GameState {
public:
    GameState();

    State current_state = State::MENU; // Change to menu for prod

    Menu menu;
    Game game;
    GameOver game_over;
    GameWin game_win;

    Music* curr_music = nullptr;

    void update();
    void draw();
    void drawUI();

private:
    void swapMusic(const std::string &new_music);
};

#endif //GAMESTATE_H
