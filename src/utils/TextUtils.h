//
// Created by Harry Skerritt on 06/07/2026.
//

#ifndef TEXTUTILS_H
#define TEXTUTILS_H
#include "raylib.h"

namespace Utils {
    inline int getCentredTextPos(const char* text, const int font_size) {
        int text_width = MeasureText(text, font_size);
        return (GetScreenWidth() / 2) - (text_width / 2);
    }
}

#endif //TEXTUTILS_H
