//
// Created by Harry Skerritt on 06/07/2026.
//

#ifndef GRID_H
#define GRID_H
#include <vector>
#include "Tile.h"
#include "raylib.h"


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


    void reset();

private:
    Tile* hovered_tile = nullptr;
    std::vector<Tile> tiles;

    float hex_size = 50.0f;
    //float centre_x = 360.0f;
    //float centre_y = 310.0f;

    float centre_x, centre_y;

    const Vector2 neighbours[6] = {
        { 0, -1 }, { 1, -1 }, { 1, 0 },
        { 0, 1 }, { -1, 1 }, { -1, 0 }
    };

    bool highlight_neighbours = false;
};



#endif //GRID_H
