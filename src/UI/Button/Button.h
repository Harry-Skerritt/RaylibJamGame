//
// Created by Harry Skerritt on 09/07/2026.
//

#ifndef BUTTON_H
#define BUTTON_H
#include "raylib.h"


class Button {
public:
    Button(const Texture2D &texture, Vector2 position, Vector2 size, const char* text, int frames = 3);

    void update(const char* new_text = "");
    void draw();

    bool isPressed() { return btn_action; }

private:
    Texture2D btn_texture;
    Vector2 btn_pos;
    Vector2 btn_size;

    Font btn_font;
    const char *btn_text;

    int btn_frames;
    float frame_height;

    int btn_state = 0;
    bool btn_action = false;

    Rectangle btn_rect;
    Rectangle btn_bounds;
};



#endif //BUTTON_H
