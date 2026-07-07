//
// Created by Harry Skerritt on 07/07/2026.
//

#include "Tile.h"
#include "raylib.h"
#include <cmath>

#include "../utils/Colours.h"
#include "../utils/Element.h"

Tile::Tile(int q, int r, int atomic_number, Vector2 pos)
    : q(q), r(r), atomic_number(atomic_number), pos(pos) {}


void Tile::draw(const float hex_size, const float centre_x, const float centre_y, const bool is_hovered, const bool is_placing) {
    float x = hex_size * (3.0f / 2.0f * q);
    float y = hex_size * (sqrt(3.0f) * (r + q / 2.0f));
    pos = { x + centre_x, y + centre_y };

    Element e = PeriodicTable[atomic_number];
    Color fill = getColourForType(e.type);

    DrawPoly(pos, 6, hex_size - 2, 0, fill);
    DrawPolyLinesEx(pos, 6, hex_size - 2, 0, 3.0f, Colours::HEX_BORDER);

    if (is_hovered && is_placing) {
        if (!isValidPlacement()) {
            DrawPolyLinesEx(pos, 6, hex_size - 2, 0, 5.0f, RED);
        } else {
            DrawPolyLinesEx(pos, 6, hex_size - 2, 0, 5.0f, Colours::TEXT_COLOUR);
        }
    } else if (is_hovered) {
        DrawPolyLinesEx(pos, 6, hex_size - 2, 0, 5.0f, Colours::TEXT_COLOUR);
    }

    if (atomic_number > 0) {
        int symbol_width = MeasureText(e.symbol, 30);
        DrawText(e.symbol, (int)pos.x - symbol_width / 2, (int)pos.y - 20, 30, DARKGRAY);

        std::string num = std::to_string(atomic_number);
        int num_width = MeasureText(num.c_str(), 15);
        DrawText(num.c_str(), (int)pos.x - num_width / 2, (int)pos.y + 20, 15, GRAY);
    }
}

bool Tile::isValidPlacement() {
    return atomic_number <= 0;
}


void Tile::drawTempTile(Vector2 screenPos, float hex_size, int atomic_number) {
    Element e = PeriodicTable[atomic_number];
    Color fill = getColourForType(e.type);

    DrawPoly(screenPos, 6, hex_size, 0, Fade(fill, 0.5f));
    DrawPolyLinesEx(screenPos, 6, hex_size, 0, 3.0f, Colours::HEX_BORDER);

    if (atomic_number > 0) {
        int symbol_width = MeasureText(e.symbol, 30);
        DrawText(e.symbol, (int)screenPos.x - symbol_width / 2, (int)screenPos.y - 20, 30, DARKGRAY);

        std::string num = std::to_string(atomic_number);
        int num_width = MeasureText(num.c_str(), 15);
        DrawText(num.c_str(), (int)screenPos.x - num_width / 2, (int)screenPos.y + 15, 15, GRAY);
    }
}



