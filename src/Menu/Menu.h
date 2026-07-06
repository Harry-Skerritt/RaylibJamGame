//
// Created by Harry Skerritt on 06/07/2026.
//

#ifndef MENU_H
#define MENU_H
#include <vector>
#include "raylib.h"

struct BGHex {
    Vector2 pos;
    float rotation;
    float speed;
};

class Menu {
public:
    Menu();
    void update();
    void draw();
    bool shouldStartGame() const { return start_game; };

private:
    bool start_game = false;
    std::vector<BGHex> bg_hexes;
};



#endif //MENU_H
