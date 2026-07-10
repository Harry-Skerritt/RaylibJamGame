//
// Created by Harry Skerritt on 06/07/2026.
//

#ifndef MENU_H
#define MENU_H
#include <vector>
#include "raylib.h"
#include "../UI/Button/Button.h"

struct BackgroundAtom {
    Vector2 pos;
    Vector2 velocity;
    float rotation;
    float rotation_speed;
};
class Menu {
public:
    Menu();
    ~Menu();

    void update();
    void draw();
    bool shouldStartGame() const { return start_game; };
    void reset() { start_game = false; };

private:
    bool start_game = false;

    void drawLogo();
    void drawStart();


    // Audio
    Button* music_button = nullptr;
    Button* sfx_button = nullptr;
    const char* music_str;
    const char* sfx_str;

    void createButtons();
    void updateButtons();


    // Background
    Texture2D background_atom;
    std::vector<BackgroundAtom> background_atoms;
    void createBackground();
    void updateBackground();
    void drawBackground();
};



#endif //MENU_H
