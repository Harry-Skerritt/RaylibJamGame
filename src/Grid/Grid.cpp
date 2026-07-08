//
// Created by Harry Skerritt on 06/07/2026.
//

#include "Grid.h"
#include "raylib.h"
#include <cmath>
#include <iostream>
#include <ostream>

#include "../utils/Element.h"

Grid::Grid() {
    for (int q = -3; q <= 3; q++) {
        for (int r = -3; r <= 3; r++) {
            if (abs(q + r) <= 3) {
                tiles.push_back({ q, r, 0, {0, 0} });
            }
        }
    }
}

void Grid::update() {
    hovered_tile = getTileAtMouse();
}

void Grid::draw(bool is_placing, Vector2 grid_pos) {
    centre_x = grid_pos.x;
    centre_y = grid_pos.y;

    for (auto& tile : tiles) tile.is_highlighted = false;

    if (highlight_neighbours) {
        if (hovered_tile != nullptr) {
            for (int i = 0; i < 6; i++) {
                Tile* n = getNeighbour(hovered_tile->q, hovered_tile->r, i);
                if (n != nullptr) {
                    n->is_highlighted = true;
                    n->neighbour = i;
                }
            }
        }
    }


    for (auto& tile : tiles) {
        bool is_hovered = (&tile == hovered_tile);
        tile.draw(hex_size, centre_x, centre_y, is_hovered, is_placing);
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

// Getters & Setters
void Grid::setTile(const int q, const int r, const int atomic_number) {
    for (auto& tile : tiles) {
        if (tile.q == q && tile.r == r) {
            tile.atomic_number = atomic_number;
        }
    }
}

Tile *Grid::getTile(const int q, const int r) {
    for (auto& tile : tiles) {
        if (tile.q == q && tile.r == r) {
            return &tile;
        }
    }
    return nullptr;
}


Tile *Grid::getNeighbour(const float q, const float r, const int neighbour) {
    auto [x, y] = neighbours[neighbour];
    const Vector2 neighbour_coords = { q + x, r + y };

    return getTile(neighbour_coords.x, neighbour_coords.y);
}




