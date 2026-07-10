//
// Created by Harry Skerritt on 07/07/2026.
//

#include "Tile.h"
#include "raylib.h"
#include <cmath>

#include "../AssetManager/AssetManager.h"
#include "../utils/Colours.h"
#include "../utils/Element.h"

Tile::Tile(int q, int r, int atomic_number, Vector2 pos, int passes)
    : q(q), r(r), atomic_number(atomic_number), pos(pos), stability_passes(passes) {}


void Tile::draw(
    const float hex_size, const float centre_x, const float centre_y, const bool is_hovered, const bool is_placing)
{
    // Pulse
    float pulse = 1.0f;
    if (is_volatile) {
        pulse = 1.0f + (sinf(GetTime() * 5.0f) * 0.1f);
    }

    float draw_size = (hex_size - 2) * pulse;
    float inner_draw_size = (hex_size - 8) * pulse;

    float x = hex_size * (3.0f / 2.0f * q);
    float y = hex_size * (sqrt(3.0f) * (r + q / 2.0f));
    pos = { x + centre_x, y + centre_y };

    Element e = PeriodicTable[atomic_number];
    Color fill = is_volatile ? Colours::VOLATILE_TILE : getColourForType(e.type);

    DrawPoly(pos, 6, draw_size, 0, fill);
    DrawPolyLinesEx(pos, 6, draw_size, 0, 3.0f, Colours::HEX_BORDER);

    if (is_hovered && is_placing) {
        if (!isValidPlacement()) {
            DrawPolyLinesEx(pos, 6, hex_size - 2, 0, 5.0f, RED);
        } else {
            DrawPolyLinesEx(pos, 6, hex_size - 2, 0, 5.0f, Colours::TEXT_COLOUR);
        }
    } else if (is_hovered) {
        DrawPolyLinesEx(pos, 6, hex_size - 2, 0, 5.0f, Colours::TEXT_COLOUR);
    }

    if (is_highlighted) DrawPolyLinesEx(pos, 6, hex_size - 2, 0, 5.0f, RED);

    if (atomic_number > 0) {
        auto symbol_font = AssetManager::GetFont("itim-40");
        auto num_font = AssetManager::GetFont("itim-20");

        int symbol_width = MeasureTextEx(symbol_font, e.symbol, 40, 2).x;
        int num_width = MeasureTextEx(num_font, std::to_string(atomic_number).c_str(), 20, 2).x;

        DrawTextEx(
            symbol_font, e.symbol,
            {pos.x - symbol_width / 2, pos.y - 30}, 40, 2, getContrastColor(fill));

        if (!is_volatile) drawHealthBar({pos.x, pos.y + 6}, stability, 1.0f);

        DrawTextEx(
            num_font, std::to_string(atomic_number).c_str(),
            {pos.x - num_width / 2, pos.y + 15}, 20, 2, getContrastColor(fill));

        DrawPolyLinesEx(pos, 6, inner_draw_size, 0, 3.0f, DARKGRAY);
    }
}

void Tile::drawHealthBar(const Vector2 pos, const float current_health, float max_health) {
    constexpr float max_width = 50.0f;
    constexpr int x_diff = 25;
    constexpr int y_diff = 2;

    float health_ratio = (max_health > 0) ? (current_health / max_health) : 0;
    if (health_ratio < 0) health_ratio = 0;
    if (health_ratio > 1) health_ratio = 1;

    float current_width = max_width * health_ratio;

    DrawRectangleGradientH(
        static_cast<int>(pos.x) - x_diff, static_cast<int>(pos.y) + y_diff, static_cast<int>(current_width), 6,
        (Color){212, 0, 0, 255}, (Color){51, 255, 0 ,255});

    DrawRectangle(static_cast<int>(pos.x) - x_diff, static_cast<int>(pos.y) + y_diff, static_cast<int>(max_width), 6, GRAY);

    DrawRectangleGradientH(
        static_cast<int>(pos.x) - x_diff, static_cast<int>(pos.y) + y_diff, static_cast<int>(current_width), 6,
        (Color){212, 0, 0, 255}, (Color){51, 255, 0 ,255});
}

Color Tile::getContrastColor(Color c) {
    float luminance = (0.299f * c.r + 0.587f * c.g + 0.114f * c.b) / 255.0f;
    return (luminance > 0.5f) ? DARKGRAY : Colours::WHITE_TEXT;
}

bool Tile::isValidPlacement() {
    return atomic_number <= 0;
}

void Tile::drawTempTile(Vector2 screenPos, float hex_size, int atomic_number) {
    Element e = PeriodicTable[atomic_number];
    Color fill = getColourForType(e.type);

    DrawPoly(screenPos, 6, hex_size, 0, Fade(fill, 0.5f));
    DrawPolyLinesEx(screenPos, 6, hex_size, 0, 3.0f, Colours::HEX_BORDER);

    // Element
    if (atomic_number > 0) {
        auto symbol_font = AssetManager::GetFont("itim-40");
        auto num_font = AssetManager::GetFont("itim-20");

        Vector2 symbol_dims = MeasureTextEx(symbol_font, e.symbol, 40, 2);
        Vector2 num_dims = MeasureTextEx(num_font, std::to_string(atomic_number).c_str(), 20, 2);

        DrawTextEx(symbol_font, e.symbol,
        { pos.x - symbol_dims.x / 2.0f, pos.y - symbol_dims.y / 1.2f },
        40, 2, getContrastColor(fill));

        DrawTextEx(num_font, std::to_string(atomic_number).c_str(),
            { pos.x - num_dims.x / 2.0f, pos.y - num_dims.y / 2.0f + 15 },
            20, 2, getContrastColor(fill));
    }
}



