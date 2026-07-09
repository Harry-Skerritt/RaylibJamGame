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
    reset();
}

void Grid::update() {
    hovered_tile = getTileAtMouse();
}

void Grid::draw(bool is_placing, Vector2 grid_pos) {
    centre_x = grid_pos.x;
    centre_y = grid_pos.y;

    for (auto& tile : tiles) {
        bool is_hovered = (&tile == hovered_tile);
        tile.draw(hex_size, centre_x, centre_y, is_hovered, is_placing);
    }
}

void Grid::reset() {
    tiles.clear();

    for (int q = -3; q <= 3; q++) {
        for (int r = -3; r <= 3; r++) {
            if (abs(q + r) <= 3) {
                tiles.push_back({ q, r, 0, {0, 0}, tile_free_goes });
            }
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

// Getters & Setters
void Grid::setTile(const int q, const int r, const int atomic_number) {
    for (auto& tile : tiles) {
        if (tile.q == q && tile.r == r) {
            tile.atomic_number = atomic_number;
            tile.stability = 1.0f;
            tile.stability_passes = tile_free_goes;
            tile.is_volatile = false;
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

int Grid::getEmptyTiles() const {
    int empty_tiles = 0;
    for (auto& tile : tiles) {
        if (tile.atomic_number == 0) empty_tiles++;
    }

    return empty_tiles;
}

// Balancing
std::vector<int> Grid::getOrphanedAtomicNumbers(int limit) {
    std::vector<int> orphans;

    for (auto& tile : tiles) {
        if (tile.atomic_number >= limit) {
            bool has_match = false;

            for (int i = 0; i < 6; i++) {
                Tile* n = getNeighbour(tile.q, tile.r, i);
                if (n && n->atomic_number == tile.atomic_number) {
                    has_match = true;
                    break;
                }
            }

            if (!has_match) orphans.push_back(tile.atomic_number);
        }
    }
    return orphans;
}

int Grid::getMinAtomicNumber() {
    int min = 999;
    for (auto& tile : tiles) {
        if (tile.atomic_number > 0) {
            min = std::min(min, tile.atomic_number);
        }
    }
    return min;
}

std::vector<Tile*> Grid::getUnstableTiles() {
    std::vector<Tile*> unstable_tiles;

    for (auto& tile : tiles) {
        if (tile.atomic_number > 0 && tile.stability < 1.0f) {
            unstable_tiles.push_back(&tile);
        }
    }

    return unstable_tiles;
}

void Grid::updateStability(Tile *tile) {
    for (auto& t : tiles) {
        if (t.atomic_number <= 0 || (t.q == tile->q && t.r == tile->r)) continue;

        if (t.getStabilityPasses() > 0) {
            t.minusPass();
        } else {
          t.changeStability(-stability_decrease);
        }

        if (t.getStability() <= 0.0f && !t.is_volatile) {
            // Tile Explosion
            t.is_volatile = true;
            return;
        }
    }
}



