//
// Created by Harry Skerritt on 10/07/2026.
//

#ifndef ICON_H
#define ICON_H
#include "raylib.h"
#include <string>

class Icon {
public:
    Icon();
    ~Icon();

    void draw(Vector2 centre, const Texture2D &texture, const std::string &key, int amt, bool active);
};



#endif //ICON_H
