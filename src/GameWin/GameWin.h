//
// Created by Harry Skerritt on 09/07/2026.
//

#ifndef GAMEWIN_H
#define GAMEWIN_H
#include "../UI/Button/Button.h"

class GameWin {
public:
    GameWin();
    ~GameWin();

    void init();
    void update();
    void draw();

    int getResultState() const { return result_state; }

private:
    Button *quit_button = nullptr;
    Button *restart_button = nullptr;

    int result_state = -1;

    Sound btn_sound;
};



#endif //GAMEWIN_H
