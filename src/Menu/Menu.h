//
// Created by Harry Skerritt on 06/07/2026.
//

#ifndef MENU_H
#define MENU_H
#include <vector>
#include "raylib.h"


class Menu {
public:
    Menu();
    ~Menu();

    void update();
    void draw();
    bool shouldStartGame() const { return start_game; };

private:
    bool start_game = false;

    void initTexture();
    void initFont(float font_size);

    void drawLogo();
    void drawStart();

    bool is_texture_loaded = false;
    Texture2D title_texture;

    bool is_font_loaded = false;
    Font font;
};



#endif //MENU_H
