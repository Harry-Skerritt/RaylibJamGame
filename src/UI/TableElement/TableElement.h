//
// Created by Harry Skerritt on 09/07/2026.
//

#ifndef TABLEELEMENT_H
#define TABLEELEMENT_H
#include "raylib.h"


class TableElement {
public:
    TableElement();
    ~TableElement();

    void init(int an);
    void draw(
        Vector2 pos, Vector2 size, bool is_filled,
        const Font* symbol_font, const int symbol_size,
        const Font* num_font, const int num_size) const;


private:
    int atomic_number;
};



#endif //TABLEELEMENT_H
