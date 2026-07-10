//
// Created by Harry Skerritt on 10/07/2026.
//

#ifndef FLOATINGTEXTMANAGER_H
#define FLOATINGTEXTMANAGER_H
#include "raylib.h"
#include <string>
#include <vector>

struct FloatingText {
    std::string text;
    Vector2 pos;
    float alpha = 1.0f;
    float lifetime = 1.5f;
};

class FloatingTextManager {
public:
    void add(std::string text, Vector2 pos);
    void update(float dt);
    void draw(Font font);

private:
    std::vector<FloatingText> texts;
};



#endif //FLOATINGTEXTMANAGER_H
