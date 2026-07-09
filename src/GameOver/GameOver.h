//
// Created by Harry Skerritt on 09/07/2026.
//

#ifndef GAMEOVER_H
#define GAMEOVER_H
#include "../Game/Game.h"
#include "../UI/Button/Button.h"


class GameOver {
public:
    GameOver();
    ~GameOver();

    void init(const Game* game);
    void update();
    void draw();

    int getResultState() const { return result_state; }

private:
    int score;

    int unlock_count;
    int total_count;

    int sacrifice_count;
    bool can_continue = false;


    Button *quit_button = nullptr;
    Button *restart_button = nullptr;
    Button *continue_button = nullptr;

    int result_state = -1;

};



#endif //GAMEOVER_H
