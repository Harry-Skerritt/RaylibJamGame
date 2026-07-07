//
// Created by Harry Skerritt on 07/07/2026.
//

#include "Tile.h"
#include "raylib.h"
#include <cmath>

#include "../AssetManager/AssetManager.h"
#include "../utils/Colours.h"
#include "../utils/Element.h"

Tile::Tile(int q, int r, int atomic_number, Vector2 pos)
    : q(q), r(r), atomic_number(atomic_number), pos(pos) {}


void Tile::draw(
    const float hex_size, const float centre_x, const float centre_y, const bool is_hovered, const bool is_placing) {
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
        auto symbol_font = AssetManager::GetFont("itim-40");
        auto num_font = AssetManager::GetFont("itim-20");

        int symbol_width = MeasureTextEx(symbol_font, e.symbol, 40, 2).x;
        int num_width = MeasureTextEx(num_font, std::to_string(atomic_number).c_str(), 20, 2).x;

        DrawTextEx(
            symbol_font, e.symbol,
            {pos.x - symbol_width / 2, pos.y - 30}, 40, 2, DARKGRAY);

        DrawTextEx(
            num_font, std::to_string(atomic_number).c_str(),
            {pos.x - num_width / 2, pos.y + 15}, 20, 2, GRAY);
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
        auto symbol_font = AssetManager::GetFont("itim-40");
        auto num_font = AssetManager::GetFont("itim-20");

        Vector2 symbol_dims = MeasureTextEx(symbol_font, e.symbol, 40, 2);
        Vector2 num_dims = MeasureTextEx(num_font, std::to_string(atomic_number).c_str(), 20, 2);

        DrawTextEx(symbol_font, e.symbol,
        { pos.x - symbol_dims.x / 2.0f, pos.y - symbol_dims.y / 1.2f },
        40, 2, DARKGRAY);

        DrawTextEx(num_font, std::to_string(atomic_number).c_str(),
            { pos.x - num_dims.x / 2.0f, pos.y - num_dims.y / 2.0f + 15 },
            20, 2, GRAY);
    }
}



