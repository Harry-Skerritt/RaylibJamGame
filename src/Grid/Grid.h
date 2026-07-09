//
// Created by Harry Skerritt on 06/07/2026.
//

#ifndef GRID_H
#define GRID_H
#include <vector>
#include "Tile.h"
#include "raylib.h"
#include "../utils/Element.h"


class Grid {
public:
    Grid();
    void update();
    void draw(bool is_placing, Vector2 grid_pos);

    void setTile(int q, int r, int atomic_number);
    Tile* getTile(int q, int r);


    Tile* getTileAtMouse();
    Tile* getNearestHex(float q, float r);
    Tile* getNeighbour(float q, float r, int neighbour);


    float getHexSize() const { return hex_size; }

    int getEmptyTiles() const;

    // Balancing
    std::vector<int> getOrphanedAtomicNumbers(int limit);
    int getMinAtomicNumber();
    std::vector<Tile*> getUnstableTiles();

    void updateStability(Tile* tile);

    void reset();

private:
    Tile* hovered_tile = nullptr;
    std::vector<Tile> tiles;

    float hex_size = 50.0f;
    float centre_x, centre_y;

    const Vector2 neighbours[6] = {
        { 0, -1 }, { 1, -1 }, { 1, 0 },
        { 0, 1 }, { -1, 1 }, { -1, 0 }
    };

    bool highlight_neighbours = false;

    int tile_free_goes = 8; // 8
    float stability_decrease = 0.1f; // 0.1f
};



#endif //GRID_H
