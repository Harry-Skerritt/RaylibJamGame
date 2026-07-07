//
// Created by Harry Skerritt on 07/07/2026.
//

#ifndef TILE_H
#define TILE_H
#include "raylib.h"


class Tile {
public:
    int q, r, atomic_number;
    Vector2 pos;

    Tile(int q, int r, int atomic_number, Vector2 pos);

    bool isValidPlacement();

    void draw(float hex_size, float centre_x, float centre_y, bool is_hovered, bool is_placing);
    void drawTempTile(Vector2 screenPos, float hex_size, int atomic_number);
};



#endif //TILE_H
