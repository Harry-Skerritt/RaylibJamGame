//
// Created by Harry Skerritt on 06/07/2026.
//

#include "Grid.h"
#include "raylib.h"
#include <cmath>
#include "../utils/Element.h"

Grid::Grid() {
    for (int q = -3; q <= 3; q++) {
        for (int r = -3; r <= 3; r++) {
            if (abs(q + r) <= 3) {
                tiles.push_back({q, r, 0});
            }
        }
    }
}

void Grid::update() {
    hovered_tile = getTileAtMouse();

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        auto tile = getTileAtMouse();
        tile->atomic_number++;
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        auto tile = getTileAtMouse();
        tile->atomic_number--;
    }
}


void Grid::draw() {
    for (auto& tile : tiles) {
        // Get Element Data
        Element e = PeriodicTable[tile.atomic_number];
        Color fill = getColourForType(e.type);

        // Get Position for tile & Draw
        float x = hex_size * (3.0f / 2.0f * tile.q);
        float y = hex_size * (sqrt(3.0f) * (tile.r + tile.q / 2.0f));
        Vector2 pos = { x + centre_x, y + centre_y};
        DrawPoly(pos, 6, hex_size - 2, 0, fill);
        DrawPolyLinesEx(pos, 6, hex_size - 2, 0, 3.0f, BLACK);

        // Draw Element Data
        if (tile.atomic_number > 0) {
            int symbol_width = MeasureText(e.symbol, 30);
            DrawText(e.symbol, (int)pos.x - symbol_width / 2, (int)pos.y - 20, 30, DARKGRAY);

            std::string num = std::to_string(tile.atomic_number);
            int num_width = MeasureText(num.c_str(), 15);
            DrawText(num.c_str(), (int)pos.x - num_width / 2, (int)pos.y + 20, 15, GRAY);
        }

        // Handle Hover
        if (&tile == hovered_tile) {
            DrawPolyLinesEx(pos, 6, hex_size - 2, 0, 5.0f, YELLOW);
        }
    }
}


// Math
Tile *Grid::getTileAtMouse() {
    Vector2 mouse = GetMousePosition();
    float x = (mouse.x - centre_x) / hex_size;
    float y = (mouse.y - centre_y) / hex_size;

    float q = (2.0f / 3.0f * x);
    float r = (-1.0f / 3.0f * x + sqrtf(3.0f) / 3.0f * y);

    return getNearestHex(q, r);
}

Tile *Grid::getNearestHex(float q, float r) {
    int q_int = round(q);
    int r_int = round(r);
    float s_int = round (-q - r);

    float q_diff = abs(q_int - q);
    float r_diff = abs(r_int - r);
    float s_diff = abs(s_int - (-q - r));

    if (q_diff > r_diff && q_diff > s_diff) q_int = -r_int - s_int;
    else if (r_diff > s_diff) r_int = -q_int - s_int;

    for (auto& tile : tiles) {
        if (tile.q == q_int && tile.r == r_int) return &tile;
    }
    return nullptr;
}

